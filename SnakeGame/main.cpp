#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <atomic>
#include <thread>

#include "Game.hpp"

/*
    Send review to Cherno: chernoreview@gmail.com
*/

/* Thread safe operations variable to store and retrieve values */
std::atomic<char> pressedKey(CHAR_INIT);

/* main functions */
static void captureInput(Game* g);
static bool playAgain(GameStatus status);
static void resetPressedKey();

int main()
{
    bool keepPlaying = TRUE;
    char key = CHAR_INIT;

    while (keepPlaying)
    {
        Game game;

        /* Capture inputs from Keyboard */
        std::thread inputThread(captureInput, &game);

        /* Refresh game and move snake */
        std::thread gameThread(runGame, &game);

        inputThread.join();
        gameThread.join();

        /* Get input from keyboard to play again (or not) */
        keepPlaying = playAgain(game.checkGameStatus());
    }

    return EXIT_SUCCESS;
}

/* Thread refresh the game  */
static void runGame(Game* g)
{
    char key = CHAR_INIT;

    /* Run the game, update the snake directions and refresh map */
    while (key != Keys::ESC)
    {
        key = pressedKey.load();

        g->refreshGame(key);

        /* if Snake hits something like walls or bite itself, finish the game */
        if (g->checkGameStatus() != GameStatus::RUNNING)
            break;

        /* Sleep time - defines game speed */
        pauseMilliSeconds(g->getSpeedGameMs());
    }
}

/* Thread for keyboard input does not be affected by refresh game pause */
static void captureInput(Game* g)
{
    char key = CHAR_INIT;

    while (g->checkGameStatus() == GameStatus::RUNNING)
    {
        /* If any keyboard key is pressed */
        if (_kbhit())
        {
            /* Save it to set new snake direction */
            key = _getch();
            pressedKey.store(key);

            if (key == Keys::ESC)
                break;
        }
    }
}


/* Reset pressed key */
static void resetPressedKey()
{
    pressedKey = CHAR_INIT;
}

static bool playAgain(GameStatus status)
{
    bool option = FALSE;

    resetPressedKey();
    Logger log;
    std::stringstream ss;

    if (status == GameStatus::WINGAME)
        ss << CRLF << " YOU WIN !!! :)" << CRLF;
    else
        ss << CRLF << " GAME OVER :(" << CRLF;

    ss << CRLF << " PLAY AGAIN ? (1 or 0): ";

    log.out(ss.str(), 0, (MapSize::MAX_Y_TEXT));

    std::cin >> option;

    /* Validate input from user */
    if (option != TRUE && option != FALSE)
        option = FALSE;

    return option;
}