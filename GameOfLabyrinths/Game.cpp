#include "Game.h"
#include <iostream>
#include <queue>

void Game::loadLevels()
{
	
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

void Game::placeWalls(vector<vector<char>>& symbols, int monsterCount)
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

	cout << "Which positions do you want to wall?\n";

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
}
