#pragma once
#include "Entity.h"
#include <vector>

class Labyrinth;
using namespace std;

class Sorceress : public Entity
{

private:

	vector<Position> path;
	vector<Position>::iterator nextStep;

	

	bool insidePortal;
	bool dead;
	
	
public:
	
	Sorceress(Position);

	void findPath(vector<vector<char>>& symbols, Position, Position);
	
	bool isInsidePortal()const;
	bool isDead()const;
	
	char getSymbol() const override;
	bool canMove() const override;
	void move(Labyrinth& labyrinth) override;

	

	
	
};






