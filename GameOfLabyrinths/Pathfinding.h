#pragma once
#include <map>
#include "Position.h"
#include "Labyrinth.h"

using namespace std;

class Pathfinding
{
public:
	
	virtual vector<Position> findPath(vector<vector<char>>&, Position, Position) = 0;
};

