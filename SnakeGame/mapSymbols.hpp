#pragma once

#include <string>

using snakeDir = char;
using mapSymbol = std::string;

struct MapSymbols
{
	static const mapSymbol SNAKE_HEAD;
	static const mapSymbol SNAKE_HEAD_DEAD;
	static const mapSymbol SNAKE_BODY;
	static const mapSymbol FOOD;
	static const mapSymbol EMPTY;
	static const mapSymbol WALL_VERTICAL;
	static const mapSymbol WALL_HORIZONTAL;
	static const mapSymbol WALL_TOP_RIGHT_CORNER;
	static const mapSymbol WALL_TOP_LEFT_CORNER;
	static const mapSymbol WALL_BOTTON_RIGHT_CORNER;
	static const mapSymbol WALL_BOTTON_LEFT_CORNER;
};

/* Define map parameters */
struct MapSize
{
	static const unsigned int MIN = 0;
	static const unsigned int MAX_X = 25;
	static const unsigned int MAX_Y = 15;
	static const unsigned int MAX_Y_TEXT  = MAX_Y + 5;
	static const unsigned int MAX_VALID_X = MAX_X - 1;
	static const unsigned int MAX_VALID_Y = MAX_Y - 1;
};

/* Used for raw data components of each map coordinate */
using mapData = unsigned int;

enum MapData
{
	EMPTY,
	V_WALL,
	H_WALL,
	SNAKE_HEAD,
	SNAKE_HEAD_DEAD,
	SNAKE_BODY,
	FOOD,
	TOP_LEFT_CORNER,
	TOP_RIGHT_CORNER,
	BOTTON_LEFT_CORNER,
	BOTTON_RIGHT_CORNER
};

enum GameStatus
{
	RUNNING,
	ENDGAME,
	WINGAME
};

/* Snakes direction, also data received from Keyboard */
struct Directions
{
	static const unsigned int UP = 72;
	static const unsigned int DOWN = 80;
	static const unsigned int LEFT = 75;
	static const unsigned int RIGHT = 77;
	static const unsigned int ESC = 27;
	static const unsigned int SPACEBAR = 32;
};

/* Aliases for structure Directions - sometimes it makes sense to refer as it as Directions and also Keys on code */
using Keys = Directions;
using Direction = Directions;
