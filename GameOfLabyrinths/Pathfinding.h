#pragma once
#include <map>
#include "Position.h"
#include "Labyrinth.h"
#include <stack>

using namespace std;

class Pathfinding
{
public:
	
	virtual stack<Position> findPath(const vector<vector<char>>&, Position, Position) = 0;
};

