#include "DFS.h"

stack<Position> DFS::findPath(const vector<vector<char>>& symbols, Position start, Position finish)
{
	

	if (start == finish)
		return { };

	int symbolsHeight = symbols.size();
	int symbolsWidth = symbols.begin()->size();

	if (start.outOfBounds(symbolsHeight, symbolsWidth))
		return { };

	vector<vector<bool>> visited(symbolsHeight);

	for (int i = 0; i < symbolsHeight; ++i)
		visited[i].resize(symbolsWidth, false);

	stack<Position> path;

	dfs(symbols, symbolsHeight, symbolsWidth , start , finish, visited, path);

	if (path.empty())
		return { };
		
	
	return makePath(path);
}

bool DFS::dfs(const vector<vector<char>>& symbols, int height, int width, Position start, Position finish, vector<vector<bool>>& visited, stack<Position>& path)
{

	if (start == finish)
	{
		path.push(finish);
		return true;
	}
	if (start.outOfBounds(height, width))
		return false;

	if (visited[start.getX()][start.getY()])
		return false;

	if (symbols[start.getX()][start.getY()] == '#')
		return false;

	if (symbols[start.getX()][start.getY()] == '$')
		return false;

	visited[start.getX()][start.getY()] = true;
	path.push(start);

	if(dfs(symbols, height, width, start + Position(1, 0), finish, visited, path))
	{
		return true;
	}

	if(dfs(symbols, height, width, start + Position(0, 1), finish, visited, path))
	{
		return true;
	}
	
	if(dfs(symbols, height, width, start + Position(-1, 0), finish, visited, path))
	{
		return true;
	}
	
	if(dfs(symbols, height, width, start + Position(0, -1), finish, visited, path))
	{
		return true;
	}


	return false;
	
}

stack<Position> DFS::makePath(stack<Position>& path)
{
	stack<Position> helper;

	while(!path.empty())
	{
		helper.push(path.top());
		path.pop();
	}

	return helper;
	
}
