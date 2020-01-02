#include "Entity.h"
#include "Labyrinth.h"

Entity::Entity(Position _position) :  position(_position)
{
	
}

Entity::Entity(const Entity& other) : position(other.getPosition())
{
	
}

Entity& Entity::operator=(const Entity& other)
{
	if(this != &other)
	{
		position = other.getPosition();
	}

	return *this;
}

Entity::~Entity() = default;


Position Entity::getPosition() const
{
	return position;
}

void Entity::updatePosition(Position _position)
{
	position = _position;
}

void Entity::swapWith(Entity* other)
{
	
	
}

void Entity::move(Labyrinth& labyrinth)
{
}

