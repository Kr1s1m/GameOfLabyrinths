#pragma once
#include "Pathfinding.h"
class DFS : public Pathfinding
{
public:

	stack<Position> findPath(const vector<vector<char>>&, Position, Position) override;
	
};

