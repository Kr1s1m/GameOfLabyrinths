
#include "Game.h"
#include <iostream>
#include  <thread>
#include <chrono>
#include "Sorceress.h"
#include "BFS.h"


string Game::loadFileName = "labyrinths.txt";
int Game::currentLevel = 0;
int Game::levelCount = 0;
Position Game::startingPosition = 0;
Position Game::portalPosition = 0;
vector<vector<vector<char>>>  Game::levels = { };
vector<int> Game::monsterCounts = { };
vector<pair<int, int>> Game::levelDimensions = { };
Entity* Game:: player = nullptr;
Labyrinth* Game::labyrinthInPlay = nullptr;
vector<bool> Game::levelStatus = { };
bool Game::playerWon = false;
bool Game::playerKilled = false;
bool Game::gameFinished = false;

int main()
{


	//Game::play();
	
	
	
	std::cout << "main function\n";



	std::vector<std::vector<char>> lab = { {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
										   {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
										   {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
									       {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
									       {'$', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '*', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', 'O'}  };


	Labyrinth labyrinth(lab, 10, 10);
	
	Sorceress* sorceress = new Sorceress({ 0, 0 });
	
	stack<Position> sorcPath;

	BFS bfs;
	Pathfinding* pathfinding = &bfs;

	sorcPath = pathfinding->findPath(lab, sorceress->getPosition(), { 9,9 });
	
	/*
	sorcPath.push({ 9,9 });
	sorcPath.push({ 8,9 });
	sorcPath.push({ 7,9 });
	sorcPath.push({ 6,9 });
	sorcPath.push({ 5,9 });
	sorcPath.push({ 4,9 });
	sorcPath.push({ 3,9 });
	sorcPath.push({ 2,9 });
	sorcPath.push({ 1,9 });
	*/
	
	sorceress->setPath(sorcPath);
	
	Entity*& sorcEntity = labyrinth.getEntityAt({ 0, 0 });
	
	delete sorcEntity;
	
	sorcEntity = sorceress;
	

	/*
	Entity*& monster = labyrinth.getEntityAt({ 5, 7 });
	
	for(int i = 0; i < 5; i ++)
	{
		system("cls");
		cout << labyrinth << "\n";
		
		monster->move(labyrinth);
		
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
		
	}
	*/
	
	//cout << labyrinth << "\n";

	/*
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			std::cout << labyrinth.getEntityAt({i, j})->getPosition().getX() << " " << labyrinth.getEntityAt({ i, j })->getPosition().getY() << "\t";
		}

		std::cout << "\n";
	}
	
	std::cout << labyrinth << endl;

	labyrinth.getEntityAt({ 9, 0 })->move(labyrinth);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << labyrinth.getEntityAt({ i, j })->getPosition().getX() << " " << labyrinth.getEntityAt({ i, j })->getPosition().getY() << "\t";
		}

		std::cout << "\n";
	}

	std::cout << labyrinth << endl;

	*/
	
	
	
	while(true)
	{
		if (labyrinth.isPlayerDead())
		{
			system("cls");
			cout << "You died\n";
			break;
			system("pause");
		}

		if(labyrinth.isPlayerInsidePortal())
		{
			system("cls");
			cout << "You won\n";
			break;
			system("pause");
		}
		
		system("cls");
		
		std::cout << labyrinth << endl;

		labyrinth.tick();
		
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
		
		
	}
	
	
	/*
	vector<Position> path;
	
	Pathfinding* pathfinding;
	BFS bfs;

	pathfinding = &bfs;

	Position start(0, 0);
	Position finish(9, 9);

	
	path = pathfinding->findPath(lab, start, finish);

	for (Position position : path)
		lab[position.getX()][position.getY()] = '%';

	for (auto& charArray : lab)
	{
		for (auto& symbol : charArray)
		{
			cout << symbol << ' ';
		}

		cout << '\n';
	}
	*/

	

	return 0;
}
