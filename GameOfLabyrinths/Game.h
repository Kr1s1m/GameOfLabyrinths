#pragma once
#include "Labyrinth.h"


struct Level
{
	vector<vector<char>> symbols;
	pair<int, int> dimensions;
	int monsterCount;
};

class Game
{
private:
	static string loadFileName;
	
	static int currentLevel;
	static char playerClass;
	static int levelCount;

	static vector<Level> levels;

	static Labyrinth* labyrinthInPlay;
	
	static bool isValidLevel(const Level&);
	static bool isValidMonsterCount(const Level&);
	
	static void printMainMenu();
	
	static void choosePlayerClass();
	static void loadLevelData( string );
	static void filterData();
	
	static void placeMonsters(Level&);
	static void placeWalls(Level&);
	
	static Position placePortal(Level&);
	static Position placePlayer(Level&);
	
	static void initializeCurrentLevel();
	static void playCurrentLevel();
	
	static void progressMessage();
	static void gameOverMessage();
	static void victoryMassage();
	

public:


	
	static void play();
	
	
	
};





