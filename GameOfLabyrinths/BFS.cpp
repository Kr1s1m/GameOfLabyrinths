#include "BFS.h"
#include <queue>

vector<Position> BFS::findPath(vector<vector<char>>& symbols, Position start, Position finish)
{
	
	queue<Position> bfsQ;

	vector<vector<bool>> visited;

	map<Position, Position> parents;

	Position direction[4] = { {-1, 0}, {0, +1}, {+1, 0}, {0, -1} };

	int symbolsHeight = symbols.size();
	int symbolsWidth = symbols.begin()->size();

	visited.resize(symbolsHeight);

	for (auto& boolArray : visited)
		boolArray.resize(symbolsWidth, false);

	if (start.outOfBounds(symbolsHeight, symbolsWidth))
		return { };

	bfsQ.push(start);
	visited[start.getX()][start.getY()] = true;
	parents[start] = Position(-10, -10);
	
	

	while(!bfsQ.empty())
	{
		Position currPosition = bfsQ.front();
		bfsQ.pop();
		visited[currPosition.getX()][currPosition.getY()] = true;

		if(currPosition == finish)
		{
			return makePath(parents, currPosition);
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

			parents[newPosition] = currPosition;
			bfsQ.push(newPosition);
		}

		
	}
	
	return {};
}

vector<Position> BFS::makePath(map<Position, Position>& parents, Position finish)
{
	vector<Position> path;
	Position pos = parents[finish];

	while(pos.getX() != -10 && pos.getY() != -10)
	{
		path.push_back(pos);
		pos = parents[pos];
		
	}

	return path;
}


