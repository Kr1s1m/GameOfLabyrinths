#pragma once
#include "Entity.h"
class Portal : public Entity
{
public:

	Portal(Position);
	
	char getSymbol() const override;
	bool canMove() const override;
};

