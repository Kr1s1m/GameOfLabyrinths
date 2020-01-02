#pragma once
#include "Labyrinth.h"

class Game
{
private:

	static int currentLevel;
	static vector<vector<char>> levels;
	static Labyrinth* labyrinthInPlay;
	static vector<bool> levelStatus;
	static bool playerWon;
	static bool playerKilled;

public:

	static void loadLevels();
	static void placeMonsters(vector<vector<char>>&, int);
	static void placeWalls(vector<vector<char>>&, int);
	
};

