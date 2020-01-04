#pragma once
#include "Entity.h"
#include <vector>
#include <stack>

class Labyrinth;
using namespace std;

class Sorceress : public Entity
{

private:
	
	stack<Position> path;
	bool moved;
	
	
	
public:
	
	Sorceress(Position);

	void findPath(vector<vector<char>>& symbols, Position, Position);

	void setPath(stack<Position>);

	
	
	char getSymbol() const override;
	bool canMove() const override;
	bool hasMoved() const override;
	void setMoved(bool) override;
	void move(Labyrinth& labyrinth) override;
	

	

	
	
};






