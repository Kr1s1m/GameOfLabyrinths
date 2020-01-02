#pragma once
#include "Pathfinding.h"

class BFS : public Pathfinding
{
public:

	vector<Position> findPath(const Labyrinth&) override;
	
};

