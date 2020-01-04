#include "Game.h"
#include <iostream>
#include <fstream>
#include <queue>
#include "BFS.h"
#include <thread>
#include <chrono>
#include <stdlib.h>     
#include <time.h>

string Game::loadFileName = "labyrinths.txt";
int Game::currentLevel = 0;
int Game::levelCount = 0;
char Game::playerClass = ' ';
vector<vector<vector<char>>>  Game::levels = { };
vector<int> Game::monsterCounts = { };
vector<pair<int, int>> Game::levelDimensions = { };
Labyrinth* Game::labyrinthInPlay = nullptr;


void Game::gameOverMessage()
{

	system("cls");

	cout << "You were killed by a monster.\n GAME OVER!\n\n";

	system("pause");

	exit(0);
	
}

void Game::victoryMassage()
{
	system("cls");

	cout << "CONGRATULATIONS YOU ESCAPED ALL LEVELS!\n YOU WIN!\n\n";

	system("pause");

	exit(0);
}

void Game::choosePlayerClass()
{
	char choice;

	system("cls");
	
	cout << "Choose class:\n\n";
	cout << "(S) Sorceress - Sorceresses can predict the future and they always pick the shortest path to the portal.\n";
	cout << "(M) Mage - Mages go in a single direction and when they encounter an obstacle they can teleport back\n\n";
	
	do
	{
		cout << "Enter \"M\" to pick Mage or \"S\" to pick Sorceress\n";
		
		cin >> choice;
	} while (choice != 'S' && choice != 'M');

	playerClass = choice;
}

void Game::loadLevelData(string fileName)
{
	
	ifstream iFile(fileName);
	
	if (!iFile) return;

	
	
	while(!iFile.eof())
	{

		int height;
		int width;
		int monsterCount;

		vector<vector<char>> symbolMatrix;

		iFile >> height >> width;

		if (height < 0 || width < 0)
			break;

		//symbolMatrix.resize(height);

		//for (auto& symbolArray : symbolMatrix)
			//symbolArray.resize(width);

		for(int i = 0; i < height; i++)
		{
			vector<char> tempCharArray;
			
			for (int j = 0; j < width; j++)
			{
				char c;
				iFile >> c;
				tempCharArray.push_back(c);
				
			}

			symbolMatrix.push_back(tempCharArray);
		}

		if (symbolMatrix.size() != height || symbolMatrix.begin()->size() != width)
			break;
		
		iFile >> monsterCount;

		pair<int, int> dimension = make_pair(height, width);
		
		levels.push_back(symbolMatrix);
		levelDimensions.push_back(dimension);
		monsterCounts.push_back(monsterCount);
		
		levelCount++;
		
		
	}
	
}

bool Game::isValidLevel(const vector<vector<char>>& symbolMatrix, Position start, Position finish, int monsterCount)
{
	
	if (symbolMatrix.empty())
		return false;
	
	if (symbolMatrix[start.getX()][start.getY()] != '.')
		return false;

	if (symbolMatrix[finish.getX()][finish.getY()] != '.')
		return false;

	if (!isValidMonsterCount(symbolMatrix, monsterCount))
		return false;

	for (auto& symbolArray : symbolMatrix)
		for (auto& symbol : symbolArray)
			if (symbol != '.' && symbol != '#')
				return false;

	BFS bfs;
	Pathfinding* pathfinding = &bfs;
	
	if(pathfinding->findPath(symbolMatrix, start, finish).empty())
		return false;

	return true;
}

bool Game::isValidMonsterCount(const vector<vector<char>>& symbolMatrix, int monsterCount)
{
	int freeSpaceCount = 0;
	
	for (auto& symbolArray : symbolMatrix)
		for (auto& symbol : symbolArray)
			if (symbol == '.')
				++freeSpaceCount;

	return (monsterCount < freeSpaceCount - 1 && monsterCount >= 0);
}



void Game::filterData()
{
	for(int i = 0; i < levels.size(); i++)
	{
		if(!isValidLevel(levels[i],{0,0},{levelDimensions[i].first - 1, levelDimensions[i].second - 1}, monsterCounts[i]))
		{
			levels.erase(levels.begin() + i);
			levelDimensions.erase(levelDimensions.begin() + i);
			monsterCounts.erase(monsterCounts.begin() + i);
		}
	}

	levelCount = levels.size();
	
	if (levels.empty())
	{
		cout << "no level data to load\n";
		system("pause");
		exit(0);
	}
}

void Game::printMainMenu()
{
	cout << "                        GAME OF LABYRINTHS                         \n";
	cout << "                          Made by: Kr1s1m                          \n\n\n\n";
	cout << "                  >Press any key to start a new game<               \n";
	cin.ignore();
	system("cls");
}

void Game::placeMonsters(vector<vector<char>>& symbols, int monsterCount)
{
	if (monsterCount == 0)
		return;
	
	int symbolsHeight = symbols.size() - 1;
	int symbolsWidth = symbols.begin()->size() - 1;

	srand(time(nullptr));

	for (int i = 0; i < monsterCount; ++i)
	{

		int monsterX = rand() % symbolsHeight;
		int monsterY = rand() % symbolsWidth;

		
		while (symbols[monsterX][monsterY] != '.')
		{
			monsterX = rand() % symbolsHeight;
			monsterY = rand() % symbolsWidth;
		}

		symbols[monsterX][monsterY] = '*';

	}
}

void Game::placeWalls(vector<vector<char>>& symbols, Position start, Position finish, int monsterCount)
{
	int emptySpace = 0;

	for (auto& symbolArray : symbols)
		for (auto& symbol : symbolArray)
			if (symbol == '.')
				++emptySpace;


	int maxWallsToPlace = emptySpace - monsterCount - 2;
	int wallsToPlace;

	system("cls");
	
	for (auto& symbolArray : symbols)
	{
		for (auto& symbol : symbolArray)
		{
			cout << symbol << ' ';
		}

		cout << '\n';
	}
		
	cout << '\n';

	cout << "How many walls do you wish to place? (cannot place more than " << maxWallsToPlace << ")\n";
	do
	{
		cin >> wallsToPlace;
	} while (wallsToPlace < 0 && wallsToPlace > maxWallsToPlace);

	

	BFS bfs;
	Pathfinding* pathfinding = &bfs;
	
	

	cout << "Which positions do you want to wall?\n";

	do {

		for (auto& symbolArray : symbols)
			for (auto& symbol : symbolArray)
				if (symbol == '$')
					symbol = '.';

		system("cls");

		for (auto& symbolArray : symbols)
		{
			for (auto& symbol : symbolArray)
			{
				cout << symbol << ' ';
			}

			cout << '\n';
		}
		
		cout << "Make sure there is a path from your hero to the portal.\n";

		queue<Position> toBePlaced;
		
		for (int i = 0; i < wallsToPlace; ++i)
		{
			int x, y;
			do
			{
				cout << "Enter valid position to wall (" << i + 1 << "):\n";
				cin >> x >> y;
			} while (x < 0 || y < 0 || x >= symbols.size() || y >= symbols.begin()->size() || symbols[x][y] != '.');
			

			toBePlaced.push({ x ,y });
		}

		while (!toBePlaced.empty())
		{
			symbols[toBePlaced.front().getX()][toBePlaced.front().getY()] = '$';
			toBePlaced.pop();
		}
		
	} while (pathfinding->findPath(symbols, start, finish).empty());

	cout << "Walls placed. Press any key to start your level.\n";
	system("pause");
	
}

Position Game::placePortal(vector<vector<char>>& symbols)
{
	int portalX = symbols.size() - 1;
	int portalY = symbols.begin()->size() - 1;
	
	symbols[portalX][portalY] = 'O';

	return { portalX , portalY };
	
}

Position Game::placePlayer(vector<vector<char>>& symbols)
{
	symbols[0][0] = playerClass;
	
	return { 0, 0 };
}

void Game::initializeCurrentLevel()
{
	if(labyrinthInPlay)
		delete labyrinthInPlay;

	Position playerPosition = placePlayer(levels[currentLevel]);
	Position portalPosition = placePortal(levels[currentLevel]);
	
	placeWalls(levels[currentLevel], playerPosition, portalPosition, monsterCounts[currentLevel]);

	placeMonsters(levels[currentLevel], monsterCounts[currentLevel]);
	
	labyrinthInPlay = new Labyrinth(levels[currentLevel], levelDimensions[currentLevel].first, levelDimensions[currentLevel].second);
	
}

void Game::playCurrentLevel()
{
	initializeCurrentLevel();
	
	int currentCurrent = currentLevel;
	
	while (currentCurrent == currentLevel)
	{
		if (labyrinthInPlay->isPlayerDead())
		{
			gameOverMessage();
		}

		if (labyrinthInPlay->isPlayerInsidePortal())
		{
			if (currentLevel < levelCount - 1)
				progressMessage();
			else
				victoryMassage();
		}

		system("cls");

		std::cout << *labyrinthInPlay << endl;

		labyrinthInPlay->tick();

		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));


	}
}

void Game::progressMessage()
{
	system("cls");
	cout << "Great! You have reached the exit portal of this level.\n";
	currentLevel++;
	system("pause");
	
}


void Game::play()
{
	printMainMenu();
	choosePlayerClass();
	loadLevelData(loadFileName);
	filterData();
	
	while(true)
	{
		playCurrentLevel();
	}
	
}
