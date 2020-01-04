#include "Monster.h"
#include "Labyrinth.h"

Monster::Monster(Position _position) : Entity(_position), moved(false)
{
	
}


char Monster::getSymbol() const
{
	return '*';
}

bool Monster::canMove() const
{
	return true;
}

bool Monster::hasMoved() const
{
	return moved;
}

void Monster::setMoved(bool _moved)
{
	moved = _moved;
}

void Monster::move(Labyrinth& labyrinth)
{


	
	Position direction[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
	//Position direction[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	
	for(Position dir : direction)
	{
		Position newPosition(dir + getPosition());

		if( newPosition.outOfBounds(labyrinth.getHeight(), labyrinth.getWidth()) )
			continue;

		if (labyrinth.getEntityAt(newPosition)->getSymbol() == '*')
			continue;

		if (labyrinth.getEntityAt(newPosition)->getSymbol() == '#')
			continue;

		if (labyrinth.getEntityAt(newPosition)->getSymbol() == 'O')
			continue;
		
		Entity* thisEntity = reinterpret_cast<Entity*>(this);
		labyrinth.moveEntity(thisEntity, newPosition);
		
		break;

		

	}
	
}
