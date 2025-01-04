#pragma once

#include <thread>
#include <chrono> // Para std::chrono::milliseconds
#include <string>

/* Usefull formaters */
constexpr auto CRLF = "\n";
constexpr auto TAB = "\t";
constexpr auto CHAR_INIT = '\0';
constexpr auto maxLoop = 10;

#define FORMAT_2_DIGITS std::setfill('0') << std::setw(2)

/* Usefull functions */
static void pauseMilliSeconds(unsigned int timeMs)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeMs));
}

static unsigned int getRandomNumber(const int max)
{
	return (std::rand() % max);
}

static void initializeRandomSeed()
{
	std::srand(static_cast<unsigned int>(time(0)));
}

struct Coord
{
	unsigned int X;
	unsigned int Y;
};

/* Pause game times used for refresh data on map */
struct Pause
{
	static const unsigned int p300ms = 300;
	static const unsigned int p250ms = 250;
	static const unsigned int p200ms = 200;
	static const unsigned int p150ms = 150;
	static const unsigned int p100ms = 100;
	static const unsigned int p75ms =   75;
};

/* Game Points for each eaten food - it is used to set the Pause */
struct GamePoints
{
	static const unsigned int LEVEL_0 = 0;
	static const unsigned int LEVEL_1 = 3;
	static const unsigned int LEVEL_2 = 6;
	static const unsigned int LEVEL_3 = 12;
	static const unsigned int LEVEL_4 = 24;
	static const unsigned int LEVEL_5 = 48;
	static const unsigned int WIN_GAME = 64;
};

struct GameLevel
{
	static const unsigned int LEVEL_0 = 0;
	static const unsigned int LEVEL_1 = 1;
	static const unsigned int LEVEL_2 = 2;
	static const unsigned int LEVEL_3 = 3;
	static const unsigned int LEVEL_4 = 4;
	static const unsigned int LEVEL_5 = 5;
};
