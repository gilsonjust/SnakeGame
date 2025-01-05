#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <windows.h>

#include "Util.hpp"
#include "mapSymbols.hpp"
#include "Logger.h"
#include "GameSounds.h"

using std::cout;
using std::endl;
using std::vector;

/* Set it to 1 to enable game sounds */
#define SOUND_ENABLED 0

class Game
{
public:
	Game();
	void refreshGame(snakeDir newDir);
	GameStatus checkGameStatus() const;
	int getSpeedGameMs();
private:
	snakeDir fixSnakeDirection(const snakeDir newDir);
	mapData getMapDataFromCoord(const Coord* c) const;
	Coord getSnakeLastBodyCoord() const;
	Coord getRandomEmptyCoord();
	Coord* getSnakeHead();
	void printMap() const;
	void updateGameStatus();
	void updateMap(const Coord* c, const mapData type);
	void updateMap(const int coordX, const int coordY, const mapData type);
	void moveSnake(const char dir);
	void placeFood();
	void printGameInfo();
	void setGameStatus(const GameStatus s);
	void incrementSnake(Coord c);
	void setLevelUp(bool l);
	bool isCoordEmpty(const Coord* c) const;
	bool checkIfSnakeHitsTheWall(const Coord* c) const;
	bool checkIfSnakeBitesItself(const Coord* c) const;
	bool checkIfSankeEatFood(const Coord* snakeHead, const Coord* food) const;
	bool isValidCoord(const Coord* c) const;
	bool compareCoord(const Coord* a, const Coord* b) const;
	bool getLevelUp();
	char getDirectionAsChar(const char dir) const; 
private:
	bool m_levelUp;
	unsigned int m_gameLevel;
	unsigned int m_points;
	snakeDir m_snakeCurrentDir;
	GameStatus m_status;
	Coord m_foodPos;
	vector<Coord> m_snake;
	mapData m_map[MapSize::MAX_X][MapSize::MAX_Y];
#if SOUND_ENABLED
	GameSounds sounds;
#endif
	mutable Logger log;
};