#pragma once
#include "Entity.h"
#include <stack>
#include <vector>

using namespace std;

class Mage : public Entity
{

private:
	
	std::stack<Position> path;
	bool moved;

public:

	Mage(Position, const vector<vector<char>>&);

	void findPath(const vector<vector<char>>& symbols, Position, Position);
	Position findPortal(const vector<vector<char>>& symbols)const;
	
	char getSymbol() const override;
	bool canMove() const override;
	bool hasMoved() const override;
	void setMoved(bool) override;
	void move(Labyrinth& labyrinth) override;
	
};

