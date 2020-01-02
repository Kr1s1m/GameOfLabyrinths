#pragma once
#include "Entity.h"

class Wall : public Entity
{
public:

	Wall(Position);

	char getSymbol() const override;
	bool canMove() const override;
	void move() override;
	
};

