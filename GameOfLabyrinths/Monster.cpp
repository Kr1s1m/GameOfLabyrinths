#include "Monster.h"
#include "Labyrinth.h"

Monster::Monster(Position _position) : Entity(_position), playerHit(false)
{
	
}

bool Monster::hasHitPlayer() const
{
	return playerHit;
}

char Monster::getSymbol() const
{
	return '*';
}

bool Monster::canMove() const
{
	return true;
}

void Monster::move(Labyrinth& labyrinth)
{
	Position direction[4] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	for(Position dir : direction)
	{
		Position newPosition(dir + getPosition());

		if( newPosition.outOfBounds(labyrinth.height(), labyrinth.width()) )
			continue;

		if (labyrinth.getEntityAt(newPosition)->getSymbol() == '#')
			continue;

		if (labyrinth.getEntityAt(newPosition)->getSymbol() == 'O')
			continue;

		Entity* thisEntity = reinterpret_cast<Entity*>(this);

		Entity*& destEntity = labyrinth.getEntityAt(newPosition);

		bool playerAtDest = false;

		if (destEntity->getSymbol() == 'S' || destEntity->getSymbol() == 'M')
			playerAtDest = true;
		
		if(labyrinth.moveEntity(thisEntity, newPosition))
		{
			if(playerAtDest)
			{
				playerHit = true;
			}

			break;
		}

	}
}
