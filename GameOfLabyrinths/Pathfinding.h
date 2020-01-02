#pragma once
#include <map>
#include "Position.h"
#include "Labyrinth.h"

using namespace std;

class Pathfinding
{
private:

	map<Position, Position> parents;
	
public:
	virtual vector<Position> findPath(const Labyrinth&) = 0;
};

