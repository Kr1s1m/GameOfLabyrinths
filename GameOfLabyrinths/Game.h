#pragma once
#include "Labyrinth.h"

class Game
{
private:
	static string loadFileName;
	
	static int currentLevel;
	static char playerClass;
	static int levelCount;
	
	static vector<vector<vector<char>>> levels;
	static vector<int> monsterCounts;
	static vector<pair<int, int>> levelDimensions;
	
	static Labyrinth* labyrinthInPlay;
	
	static bool isValidLevel(const vector<vector<char>>&, Position, Position, int);
	static bool isValidMonsterCount(const vector<vector<char>>&, int);
	
	static void printMainMenu();
	
	static void choosePlayerClass();
	static void loadLevelData( string );
	static void filterData();
	
	static void placeMonsters(vector<vector<char>>&, int);
	static void placeWalls(vector<vector<char>>&,Position,Position, int);
	
	static Position placePortal(vector<vector<char>>&);
	static Position placePlayer(vector<vector<char>>&);
	
	static void initializeCurrentLevel();
	static void playCurrentLevel();
	
	static void progressMessage();
	static void gameOverMessage();
	static void victoryMassage();
	

public:


	
	static void play();
	
	
	
};





