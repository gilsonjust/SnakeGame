#pragma once

#include <windows.h>

/* Windows dll added to play a sound when Snake eats food */
#pragma comment(lib, "winmm.lib")

class GameSounds
{
public:
	GameSounds() = default;
	void playSoundGameOver();
	void playSoundEatFood();
	void playSoundLevelUp();
};

