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

using std::cout;
using std::endl;
using std::vector;

class Game
{
public:
	Game();
	void refreshGame(snakeDir newDir);
	GameStatus checkGameStatus() const;
	int getSpeedGameMs() const;
private:
	void printMap() const;
	snakeDir fixSnakeDirection(const snakeDir newDir);
	mapData getMapTypeFromCoord(const Coord* c) const;
	Coord getSnakeLastBodyCoord() const;
	void updateGameStatus();
	void updateMap(const Coord* c, const mapData type);
	void updateMap(const int coordX, const int coordY, const mapData type);
	void moveSnake(const char dir);
	bool isCoordEmpty(const Coord* c) const;
	bool checkIfSnakeHitsTheWall(const Coord* c) const;
	bool checkIfSnakeBitesItself(const Coord* c) const;
	bool checkIfSankeEatFood(const Coord* snakeHead, const Coord* food) const;
	bool isValidCoord(const Coord* c) const;
	void placeFood();
	Coord getRandomEmptyCoord();
	void printGameInfo();
	bool compareCoord(const Coord* a, const Coord* b) const;
	char getDirectionAsChar(const char dir) const;
	void setGameStatus(const GameStatus s);
	void incrementSnake(Coord c);
	Coord* getSnakeHead();
private:
	unsigned int m_points;
	snakeDir m_snakeCurrentDir;
	GameStatus m_status;
	Coord m_foodPos;
	vector<Coord> m_snake;
	mapData m_map[MapSize::MAX_X][MapSize::MAX_Y];
	mutable Logger log;
};