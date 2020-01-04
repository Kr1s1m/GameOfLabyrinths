#pragma once
#include "Pathfinding.h"

class BFS : public Pathfinding
{
public:

	
	
	stack<Position> findPath(const vector<vector<char>>&, Position, Position) override;
	stack<Position> makePath(const vector<vector<Position>>&, const Position&, const Position&);

	
	
};

