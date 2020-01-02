#pragma once
#include "Entity.h"
class Composition : public Entity
{
private:
	
	Entity* first;
	Entity* second;
	
public:

	Composition(Position, Entity*, Entity*);


	Entity* getFirst() const;
	
	Entity* getSecond() const;
	

	char getSymbol() const override;
	bool canMove() const override;
	void move(Labyrinth& labyrinth) override;
};

