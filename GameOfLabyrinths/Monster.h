#pragma once
#include "Entity.h"

class Monster : public Entity
{
private:
	
	bool playerHit;
	
public:

	Monster(Position);

	bool hasHitPlayer()const;
	
	char getSymbol() const override;
	bool canMove() const override;
	void move(Labyrinth& labyrinth) override;

	

	
};

