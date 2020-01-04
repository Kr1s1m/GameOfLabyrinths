#pragma once
#include "Entity.h"
#include <stack>
#include <vector>

using namespace std;

class Mage : public Entity
{
	std::stack<Position> path;




public:

	Mage(Position);

	void findPath(vector<vector<char>>& symbols, Position, Position);

	void setPath(stack<Position>&);

	char getSymbol() const override;
	bool canMove() const override;
	void move(Labyrinth& labyrinth) override;
	
};

