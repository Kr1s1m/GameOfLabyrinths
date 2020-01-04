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
vector<Level> Game::levels = { };
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

		Level newLevel{ symbolMatrix, dimension, monsterCount };
		levels.push_back(newLevel);
		
		levelCount++;
		
		
	}
	
}

bool Game::isValidLevel(const Level& level)
{
	Position start = { 0, 0 };
	Position finish = { level.dimensions.first - 1, level.dimensions.second - 1 };
	
	if (level.symbols.empty())
		return false;
	
	if (level.symbols[start.getX()][start.getY()] != '.')
		return false;

	if (level.symbols[finish.getX()][finish.getY()] != '.')
		return false;

	if (!isValidMonsterCount(level))
		return false;

	for (auto& symbolArray : level.symbols)
		for (auto& symbol : symbolArray)
			if (symbol != '.' && symbol != '#')
				return false;

	BFS bfs;
	Pathfinding* pathfinding = &bfs;
	
	if(pathfinding->findPath(level.symbols, start, finish).empty())
		return false;

	return true;
}

bool Game::isValidMonsterCount(const Level& level)
{
	int freeSpaceCount = 0;
	
	for (auto& symbolArray : level.symbols)
		for (auto& symbol : symbolArray)
			if (symbol == '.')
				++freeSpaceCount;

	return (level.monsterCount < freeSpaceCount - 1 && level.monsterCount >= 0);
}



void Game::filterData()
{

	levels.erase(remove_if(levels.begin(), levels.end(), [](const Level& lvl)
	{
		
			return !isValidLevel(lvl);
		
	}), levels.end());

	levelCount = levels.size();

	
	std::sort(levels.begin(), levels.end(), [](const Level& left, const Level& right)
	{
			if (left.dimensions != right.dimensions)
				return (left.dimensions.first * left.dimensions.second < right.dimensions.first * right.dimensions.second);
			else
				return (left.monsterCount < right.monsterCount);
	});
	
	
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

void Game::placeMonsters(Level& level)
{
	if (level.monsterCount == 0)
		return;
	
	int symbolsHeight = level.symbols.size() - 1;
	int symbolsWidth = level.symbols.begin()->size() - 1;

	srand(time(NULL));

	for (int i = 0; i < level.monsterCount; ++i)
	{

		int monsterX = rand() % symbolsHeight;
		int monsterY = rand() % symbolsWidth;

		
		while (level.symbols[monsterX][monsterY] != '.')
		{
			monsterX = rand() % symbolsHeight;
			monsterY = rand() % symbolsWidth;
		}

		level.symbols[monsterX][monsterY] = '*';

	}
}

void Game::placeWalls(Level& level)
{
	Position start = { 0, 0 };
	Position finish = { level.dimensions.first - 1, level.dimensions.second - 1 };
	
	int emptySpace = 0;

	for (auto& symbolArray : level.symbols)
		for (auto& symbol : symbolArray)
			if (symbol == '.')
				++emptySpace;


	int maxWallsToPlace = emptySpace - level.monsterCount - 2;
	int wallsToPlace;

	system("cls");
	
	for (auto& symbolArray : level.symbols)
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

	if (wallsToPlace == 0)
		return;

	BFS bfs;
	Pathfinding* pathfinding = &bfs;
	
	

	cout << "Which positions do you want to wall?\n";

	do {

		for (auto& symbolArray : level.symbols)
			for (auto& symbol : symbolArray)
				if (symbol == '$')
					symbol = '.';

		system("cls");

		for (auto& symbolArray : level.symbols)
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
			} while (x < 0 || y < 0 || x >= level.dimensions.first || y >= level.dimensions.second || level.symbols[x][y] != '.');
			

			toBePlaced.push({ x ,y });
		}

		while (!toBePlaced.empty())
		{
			level.symbols[toBePlaced.front().getX()][toBePlaced.front().getY()] = '$';
			toBePlaced.pop();
		}
		
	} while (pathfinding->findPath(level.symbols, start, finish).empty());

	cout << "Walls placed. Press any key to start your level.\n";
	system("pause");
	
}

Position Game::placePortal(Level& level)
{
	int portalX = level.dimensions.first - 1;
	int portalY = level.dimensions.second - 1;
	
	
	level.symbols[portalX][portalY] = 'O';

	return { portalX , portalY };
	
}

Position Game::placePlayer(Level& level)
{
	level.symbols[0][0] = playerClass;
	
	return { 0, 0 };
}

void Game::initializeCurrentLevel()
{
	if(labyrinthInPlay)
		delete labyrinthInPlay;

	Position playerPosition = placePlayer(levels[currentLevel]);
	Position portalPosition = placePortal(levels[currentLevel]);
	
	placeWalls(levels[currentLevel]);

	placeMonsters(levels[currentLevel]);
	
	labyrinthInPlay = new Labyrinth(levels[currentLevel].symbols, levels[currentLevel].dimensions.first, levels[currentLevel].dimensions.second);
	
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
