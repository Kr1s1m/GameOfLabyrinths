#pragma once
#include "Entity.h"

class Empty : public Entity
{
public:

	Empty(Position);

	char getSymbol() const override;
	bool canMove() const override;
	void move() override;
	
};

