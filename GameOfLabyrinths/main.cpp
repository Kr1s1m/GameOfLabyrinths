#include <iostream>
#include <vector>
#include "Labyrinth.h"
#include "BFS.h"


int main()
{
	std::cout << "main function\n";



	std::vector<std::vector<char>> lab = { {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
										   {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
										   {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
									       {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
									       {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'}  };

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
		

	return 0;
}
