#include "Labyrinth.h"
#include "Empty.h"
#include "Wall.h"
#include <iostream>
#include <queue>
#include "Sorceress.h"
#include "Monster.h"
#include "Portal.h"
#include "Playerwall.h"
#include "Composition.h"

Entity* Labyrinth::createEntity(char symbol, Position position)
{
	if(symbol == '#')
		return new Wall(position);
	else if (symbol == 'S')
		return new Sorceress(position);
	else if (symbol == '*')
		return new Monster(position);
	else if (symbol == 'O')
		return new Portal(position);
	else if(symbol == '$')
		return new Playerwall(position);

	return new Empty(position);
}

void Labyrinth::fillEntities(vector<vector<char>>& symbols)
{

	

	for(int i = 0; i < symbols.size(); ++i)
	{
		for(int j = 0; j < symbols[i].size(); ++j)
		{
			entities[i][j] = createEntity(i, j);
			
		}
	}

}

Labyrinth::Labyrinth(vector<vector<char>>& symbols, int _monsterCount) : monsterCount(_monsterCount)
{
	fillEntities(symbols);
}

vector<Entity*> Labyrinth::operator[](int index)
{
	if(index > entities.size() || index < 0)
	{
		cout << "array index out of bound";

		exit(0);
	}

	return entities[index];

}

int Labyrinth::width() const
{
	return entities.begin()->size();
}

int Labyrinth::height() const
{
	return entities.size();
}

Entity*& Labyrinth::getEntityAt(Position position) 
{
	return entities[position.getX()][position.getY()];
}

void Labyrinth::swapEntities(Position srcPos, Position destPos)
{
	swap(getEntityAt(srcPos), getEntityAt(destPos));
}

bool Labyrinth::moveEntity(Entity*& entity, Position destinationPosition)
{
	Entity*& destEntity = getEntityAt(destinationPosition);
	Position sourcePosition = entity->getPosition();
	Entity*& sourceEntity = getEntityAt(sourcePosition);
	
	if (destEntity->getSymbol() == '.')
	{
		if (typeid(sourceEntity) == typeid(Composition))
		{
			auto sourceEntityFirst = reinterpret_cast<Composition*>(sourceEntity)->getFirst();
			delete sourceEntity;
			sourceEntity = sourceEntityFirst;
			delete destEntity;
			destEntity = entity;
		}
		else
		{
			swap(entity, destEntity);
			destEntity->updatePosition(sourcePosition);
		}
			
	}
	else
	{

		if (typeid(destEntity) == typeid(Composition))
			return false;
		
		Entity* newComp = new Composition(destinationPosition, destEntity, entity);
		delete destEntity;
		destEntity = newComp;

		

		if(typeid(sourceEntity) == typeid(Composition))
		{
			auto sourceEntityFirst = reinterpret_cast<Composition*>(sourceEntity)->getFirst();
			
			delete sourceEntity;
			
			sourceEntity = sourceEntityFirst;
			
		}
		else
		{
			delete sourceEntity;
			
			sourceEntity = new Empty(sourcePosition);

		}
			
	}
	
	entity->updatePosition(destinationPosition);

	return true;
	
	
}

Position Labyrinth::getPortalPosition() const
{
	
	for (auto& entityArray : entities)
	{
		for (auto& entity : entityArray)
		{
			if (entity->getSymbol() == 'O')
				return Position(entity->getPosition());
		}
		
	}
}


ostream& operator<<(ostream& os, const Labyrinth& labyrinth)
{
	for(auto& entityArray : labyrinth.entities)
	{
		for(auto& entity : entityArray)
		{
			os << entity->getSymbol() << ' ';
		}

		os << '\n';
	}

	return os;
}

