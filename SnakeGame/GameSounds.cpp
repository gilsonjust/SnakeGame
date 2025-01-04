#include "GameSounds.h"

void GameSounds::playSoundGameOver()
{
	PlaySound(TEXT("wav/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void GameSounds::playSoundEatFood()
{
	PlaySound(TEXT("wav/food.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void GameSounds::playSoundLevelUp()
{
	PlaySound(TEXT("wav/levelUp.wav"), NULL, SND_FILENAME | SND_ASYNC);
}