#pragma once
#include "Pathfinding.h"
class DFS : public Pathfinding
{
public:

	vector<Position> findPath(vector<vector<char>>&, Position, Position) override;
	
};

