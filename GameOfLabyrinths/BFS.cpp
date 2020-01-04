#include "BFS.h"
#include <queue>
#include <iostream>

stack<Position> BFS::findPath(const vector<vector<char>>& symbols, Position start, Position finish)
{
	
	if (start == finish)
		return { };

	int symbolsHeight = symbols.size();
	int symbolsWidth = symbols.begin()->size();

	if (start.outOfBounds(symbolsHeight, symbolsWidth))
		return { };

	queue<Position> bfsQ;
	
	vector<vector<bool>> visited(symbolsHeight);

	vector<vector<int>> distance(symbolsHeight);

	vector<vector<Position> > hasComeFrom(symbolsHeight);

	Position direction[4] = { {-1, 0}, {0, +1}, {+1, 0}, {0, -1} };

	for(size_t row = 0; row < symbolsHeight; row++)
	{
		visited[row].resize(symbolsWidth, false);
		distance[row].resize(symbolsWidth, symbolsWidth * symbolsHeight);
		hasComeFrom[row].resize(symbolsWidth);
	}
	
	

	bfsQ.push(start);
	visited[start.getX()][start.getY()] = true;
	distance[start.getX()][start.getY()] = 0;
	hasComeFrom[start.getX()][start.getY()] = Position(-10, -10);

	while(!bfsQ.empty())
	{
		Position currPosition = bfsQ.front();
		bfsQ.pop();
	
		if(currPosition == finish)
		{
			return makePath(hasComeFrom, currPosition);
		}
		
		for(Position dir : direction)
		{
			Position newPosition(currPosition + dir);

			if(newPosition.outOfBounds(symbolsHeight, symbolsWidth))
				continue;
			
			if(visited[newPosition.getX()][newPosition.getY()])
				continue;
			
			if (symbols[newPosition.getX()][newPosition.getY()] == '#')
				continue;

			if (symbols[newPosition.getX()][newPosition.getY()] == '$')
				continue;

			if (distance[newPosition.getX()][newPosition.getY()] < distance[currPosition.getX()][currPosition.getY()] + 1)
				continue;

			hasComeFrom[newPosition.getX()][newPosition.getY()] = currPosition;
			
			visited[currPosition.getX()][currPosition.getY()] = true;
			distance[newPosition.getX()][newPosition.getY()] = distance[currPosition.getX()][currPosition.getY()] + 1;
			bfsQ.push(newPosition);
			
		}
	}
	
	return {};
}

stack<Position> BFS::makePath(const std::vector<std::vector<Position>>& parents, const Position& finish)
{
	stack<Position> path;
	Position pos = finish;

	while (pos.getX() != -10 && pos.getY() != -10)
	{
		path.push(pos);
		pos = parents[pos.getX()][pos.getY()];

	}

	return path;
}


