#pragma once
#include "Entity.h"
#include <vector>
#include <ostream>

using namespace std;

class Labyrinth
{
private:


	vector< vector < Entity* > > entities;
	
	
	int width;
	int height;

	bool playerInsidePortal;
	bool playerDead;
	


	Entity* createEntity(char, Position, const vector<vector<char>>&);
	void fillEntities(vector<vector<char>>&);
	

public:
	
	Labyrinth(vector<vector<char>>&, int, int);

	vector<Entity*> operator[](int);

	int getWidth() const;
	int getHeight() const;

	bool isPlayerInsidePortal() const;
	bool isPlayerDead() const;

	
	Entity*& getEntityAt(Position);
	void swapEntities(Position, Position);

	bool moveEntity(Entity*&, Position);

	Position getPortalPosition() const;

	void tick();
	

	
	
	friend ostream& operator<<(ostream&, const Labyrinth&);
	
};







