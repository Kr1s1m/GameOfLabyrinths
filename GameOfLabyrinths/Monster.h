#pragma once
#include "Entity.h"

class Monster : public Entity
{
private:
	
	bool moved;
	
public:

	Monster(Position);


	
	char getSymbol() const override;
	bool canMove() const override;
	bool hasMoved() const override;
	void setMoved(bool) override;
	void move(Labyrinth& labyrinth) override;
	

	

	
};

