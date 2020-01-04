#pragma once
#include "Pathfinding.h"
class DFS : public Pathfinding
{
public:

	stack<Position> findPath(const vector<vector<char>>&, Position, Position) override;
	bool dfs(const vector<vector<char>>&,int,int, Position, Position, vector<vector<bool>>&, stack<Position>&);
	stack<Position> makePath(stack<Position>&);
	
};

