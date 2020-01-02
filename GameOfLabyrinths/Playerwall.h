#pragma once
#include "Entity.h"
class Playerwall :
	public Entity
{
	public:
	
	Playerwall(Position);
	
	char getSymbol() const override;

	bool canMove() const override;
	
};

