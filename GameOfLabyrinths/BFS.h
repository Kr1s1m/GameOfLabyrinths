#pragma once
#include "Pathfinding.h"

class BFS : public Pathfinding
{
public:

	
	
	stack<Position> findPath(const vector<vector<char>>&, Position, Position) override;
	stack<Position> makePath(const std::vector<std::vector<Position>>&, const Position&);

	
	
};

