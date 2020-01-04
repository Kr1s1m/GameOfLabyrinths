#pragma once
#include "Labyrinth.h"

class Game
{
private:
	
	static int currentLevel;
	static int levelCount;
	static Position startingPosition;
	static Position portalPosition;
	static vector<vector<vector<char>>> levels;
	static vector<int> monsterCounts;
	static vector<pair<int, int>> levelDimensions;
	static Entity* player;
	static Labyrinth* labyrinthInPlay;
	static vector<bool> levelStatus;
	static bool playerWon;
	static bool playerKilled;
	static bool gameFinished;
	static bool isValidLevel(const vector<vector<char>>&, Position, Position);
	static bool isValidMonsterCount(const vector<vector<char>>&, int);
	static bool areVaildDimensions(const pair<int, int>&, const vector<vector<char>>&);
	static void filterData();
	static void printMainMenu();
	static void choosePlayerClass();
	static void loadLevelData( string );
	static void placeMonsters(vector<vector<char>>&, int);
	static void placeWalls(vector<vector<char>>&,Position,Position, int);
	static void playCurrentLevel();
	static void progressToNextLevel();
	
	static void gameOverMessage();
	static void victoryMassage();
	

public:

	
	static string loadFileName;
	static void play();
	
	
	
};



