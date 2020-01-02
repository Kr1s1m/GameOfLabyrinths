#pragma once
#include "Pathfinding.h"

class BFS : public Pathfinding
{
public:

	
	
	vector<Position> findPath(vector<vector<char>>&, Position, Position) override;
	vector<Position> makePath(map<Position, Position>&, Position);
	
	
	
};

