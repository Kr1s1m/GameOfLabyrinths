#pragma once
#include "Pathfinding.h"
class DFS : public Pathfinding
{
public:

	vector<Position> findPath(const Labyrinth&) override;
	
};

