#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <atomic>
#include <thread>

#include "Game.hpp"

/*
    Send review to Cherno: chernoreview@gmail.com
    it is working !
*/

/* Thread safe operations variable to store and retrieve values */
std::atomic<char> pressedKey(CHAR_INIT);

/* main functions */
static void captureInput(Game* g);
static bool playAgain(GameStatus status);
static void resetPressedKey();

int main()
{
    bool option = TRUE;

    while (option)
    {
        Game game;
        bool pausedGame = false;

        /* Create a thead to capture data from keyboard */
        std::thread inputThread(captureInput, &game);

        /* Run the game, update the snake directions and refresh map */
        while (pressedKey.load() != Keys::ESC)
        {
            /* Pause game if press SPACEBAR - useful for debugging */
            if (pressedKey.load() == Keys::SPACEBAR)
            {
                resetPressedKey();
                pausedGame = !pausedGame;
            }

            if(!pausedGame)
                game.refreshGame(pressedKey.load());

            /* if Snake hits something like walls or bite itself, finish the game */
            if (game.checkGameStatus() != GameStatus::RUNNING)
                break;

            /* Sleep time - defines game speed */
            pauseMilliSeconds(game.getSpeedGameMs());
        }

        inputThread.join();

        option = playAgain(game.checkGameStatus());
    }

    return EXIT_SUCCESS;
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