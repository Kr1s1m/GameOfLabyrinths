#include "Game.h"
#include <iostream>
#include <fstream>
#include <queue>
#include "BFS.h"
#include "Sorceress.h"
#include "Mage.h"



void Game::gameOverMessage()
{

	system("cls");

	cout << "You were killed by a monster.\n GAME OVER!\n\n";

	system("pause");
	
}

void Game::victoryMassage()
{
	system("cls");

	cout << "CONGRATULATIONS YOU ESCAPED ALL LEVELS!\n YOU WIN!\n\n";

	system("pause");
}

void Game::choosePlayerClass()
{
	char choice;

	system("cls");
	
	cout << "Choose class:\n\n";
	cout << "(s) Sorceress - Sorceresses can predict the future and they always pick the shortest path to the portal.\n";
	cout << "(m) Mage - Mages go in a single direction and when they encounter an obstacle they can teleport back\n";
	
	do
	{
		cout << "Enter \"m\" to pick Mage or \"s\" to pick Sorceress\n ";
		
		cin >> choice;
	} while (choice != 's' && choice);

	if(choice == 's')
	{
		Sorceress* sorceress = new Sorceress(startingPosition);
		player = sorceress;
	}
	if(choice == 'm')
	{
		Mage* mage = new Mage(startingPosition);
		player = mage;
	}
}

void Game::loadLevelData(string fileName)
{
	
	
	ifstream iFile(fileName);
	
	if (!iFile) return;

	int levelIndex = 0;
	
	while(!iFile.eof())
	{
		int height;
		int width;

		vector<vector<char>> symbolMatrix;

		iFile >> height >> width;

		symbolMatrix.resize(height);

		for (auto& symbolArray : symbolMatrix)
			symbolMatrix.resize(width);

		for(int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				char c;
				iFile >> c;
				symbolMatrix[i][j] = c;
				
			}
		}

		levels.push_back(symbolMatrix);
		levelDimensions.push_back(make_pair(height, width));
		
		
		levelCount++;
		
		
	}
	
}

bool Game::isValidLevel(const vector<vector<char>>& symbolMatrix, Position start, Position finish)
{
	
	
	if (symbolMatrix.empty())
		return false;
	
	if (symbolMatrix[start.getX()][start.getY()] != '.')
		return false;

	if (symbolMatrix[finish.getX()][finish.getY()])
		return false;

	for (auto& symbolArray : symbolMatrix)
		for (auto& symbol : symbolArray)
			if (symbol != '.' && symbol != '#')
				return false;

	Pathfinding* pathfinding;
	BFS bfs;
	pathfinding = &bfs;
	
	if (pathfinding->findPath(symbolMatrix, start, finish).empty())
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

	return (monsterCount == freeSpaceCount - 1);
}

bool Game::areVaildDimensions(const pair<int, int>& dimension, const vector<vector<char>>& level)
{
	return (	 dimension.first > 0 
		      && dimension.second > 0 
			  && dimension.first < level.size() 
			  && dimension.second < level.begin()->size()  );
}

void Game::filterData()
{
	for(int i = 0; i < levels.size(); i++)
	{
		if(!isValidLevel(levels[i],{0,0},{levelDimensions[i].first, levelDimensions[i].second}) ||
			!isValidMonsterCount(levels[i], monsterCounts[i]) || !areVaildDimensions(levelDimensions[i], levels[i]))
		{
			levels.erase(levels.begin() + i);
			levelDimensions.erase(levelDimensions.begin() + i);
			monsterCounts.erase(monsterCounts.begin() + i);
		}
	}

	levelCount = levels.size();
	
	if (levels.empty())
		gameFinished = true;
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
	int symbolsHeight = symbols.size();
	int symbolsWidth = symbols[0].size();

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

	cout << "How many walls do you wish to place? (cannot place more than " << maxWallsToPlace << ")\n";
	do
	{
		cin >> wallsToPlace;
	} while (wallsToPlace >= 0 && wallsToPlace <= maxWallsToPlace);

	queue<Position> toBePlaced;

	BFS bfs;
	Pathfinding* pathfinding = &bfs;
	
	

	cout << "Which positions do you want to wall?\n";

	do {

		cout << "Make sure there is a path from your hero to the portal.\n";

		for (int i = 0; i < wallsToPlace; ++i)
		{
			int x, y;
			cin >> x >> y;

			toBePlaced.push({ x ,y });
		}

		while (!toBePlaced.empty())
		{
			symbols[toBePlaced.front().getX()][toBePlaced.front().getY()] = '$';
			toBePlaced.pop();
		}
		
	} while (pathfinding->findPath(symbols, start, finish).empty());
}

void Game::play()
{
	printMainMenu();
	choosePlayerClass();
	loadLevelData(loadFileName);
	filterData();
}
