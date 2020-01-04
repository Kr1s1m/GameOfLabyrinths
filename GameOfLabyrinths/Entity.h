#pragma once
#include "Position.h"

class Labyrinth;


class Entity
{
	
private:
	
	Position position;
	
	
public:
	
	Entity(Position);
	Entity(const Entity&);
	Entity& operator=(const Entity&);
	
	virtual ~Entity();

	Position getPosition() const;
	void updatePosition(Position);

	void swapWith(Entity*);
	
	virtual char getSymbol()const = 0;
	virtual bool canMove()const = 0;
	virtual bool hasMoved()const;
	virtual void setMoved(bool);
	virtual void move(Labyrinth& labyrinth);
	
	
};

