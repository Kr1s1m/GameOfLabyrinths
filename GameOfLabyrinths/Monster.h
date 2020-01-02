#pragma once
#include "Entity.h"

class Monster : public Entity
{
public:

	Monster(Position);
	
	char getSymbol() const override;
	bool canMove() const override;
	void move(Labyrinth& labyrinth) override;

	
};

