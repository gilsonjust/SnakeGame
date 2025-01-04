#pragma once

#include "Game.hpp"

Game::Game()
{
	log.clearScreen();
	initializeRandomSeed();
	setGameStatus(GameStatus::RUNNING);

	m_snakeCurrentDir = CHAR_INIT;
	m_points = GamePoints::MIN;

	/* Set the snake on center of the map */
	Coord snakeHead = { MapSize::MAX_X / 2, MapSize::MAX_Y / 2 };
	incrementSnake(snakeHead);

	char c = 0;

	/* Set map initial positions */
	for (int y = MapSize::MIN; y < MapSize::MAX_Y; y++)
	{
		for (int x = MapSize::MIN; x < MapSize::MAX_X; x++)
		{
			if (x == MapSize::MIN && y == MapSize::MIN)
				c = MapData::TOP_LEFT_CORNER;
			else if (x == MapSize::MAX_VALID_X && y == MapSize::MIN)
				c = MapData::TOP_RIGHT_CORNER;
			else if (x == MapSize::MIN && y == (MapSize::MAX_VALID_Y))
				c = MapData::BOTTON_LEFT_CORNER;
			else if (x == MapSize::MAX_VALID_X && y == MapSize::MAX_VALID_Y)
				c = MapData::BOTTON_RIGHT_CORNER;
			else if (x == MapSize::MIN || x == MapSize::MAX_VALID_X)
				c = MapData::V_WALL;
			else if (y == MapSize::MIN || y == MapSize::MAX_VALID_Y)
				c = MapData::H_WALL;
			else if (x == snakeHead.X && y == snakeHead.Y)
				c = MapData::SNAKE_HEAD;
			else if (x == m_foodPos.X && y == m_foodPos.Y)
				c = MapData::FOOD;
			else
				c = MapData::EMPTY;

			updateMap(x, y, c);
		}
	}

	placeFood();
	refreshGame(m_snakeCurrentDir);
}

void Game::refreshGame(snakeDir newDir)
{
	/* Validate new direction received from keyboard */
	snakeDir dir = fixSnakeDirection(newDir);

	/* Move snake throught the MAP */
	moveSnake(dir);

	/* Update game status if snake hits the wall, bites itself or eat food */
	updateGameStatus();

	/* Print game info on top of screen */
	printGameInfo();

	/* Draw the map and all stuff on it */
	printMap();
}

GameStatus Game::checkGameStatus() const
{
	return m_status;
}

int Game::getSpeedGameMs() const
{
	if (m_points >= GamePoints::MIN && m_points < GamePoints::LEVEL_A)
		return Pause::p300ms;

	if (m_points >= GamePoints::LEVEL_A && m_points < GamePoints::LEVEL_B)
		return Pause::p250ms;

	if (m_points >= GamePoints::LEVEL_B && m_points < GamePoints::LEVEL_C)
		return Pause::p200ms;

	if (m_points >= GamePoints::LEVEL_C && m_points < GamePoints::LEVEL_D)
		return Pause::p150ms;

	if (m_points >= GamePoints::LEVEL_D && m_points < GamePoints::LEVEL_MAX)
		return Pause::p100ms;

	if (m_points >= GamePoints::LEVEL_MAX)
		return Pause::p75ms;

	return Pause::p300ms;
}

void Game::printMap() const
{
	std::stringstream ss;

	/* Draw the map and stuff on it */
	for (int y = MapSize::MIN; y < MapSize::MAX_Y; y++)
	{
		ss << TAB;

		for (int x = MapSize::MIN; x < MapSize::MAX_X; x++)
		{
			switch (m_map[x][y])
			{
				/* Set map borders */
				case MapData::V_WALL:
					ss << MapSymbols::WALL_VERTICAL; break;

				case MapData::H_WALL:
					ss << MapSymbols::WALL_HORIZONTAL; break;

				case MapData::TOP_LEFT_CORNER:
					ss << MapSymbols::WALL_TOP_LEFT_CORNER; break;

				case MapData::TOP_RIGHT_CORNER:
					ss << MapSymbols::WALL_TOP_RIGHT_CORNER; break;

				case MapData::BOTTON_LEFT_CORNER:
					ss << MapSymbols::WALL_BOTTON_LEFT_CORNER; break;

				case MapData::BOTTON_RIGHT_CORNER:
					ss << MapSymbols::WALL_BOTTON_RIGHT_CORNER; break;

				/* Set game stuff */
				case MapData::SNAKE_HEAD:
					ss << MapSymbols::SNAKE_HEAD; break;

				case MapData::SNAKE_HEAD_DEAD:
					ss << MapSymbols::SNAKE_HEAD_DEAD; break;

				case MapData::SNAKE_BODY:
					ss << MapSymbols::SNAKE_BODY; break;

				case MapData::FOOD:
					ss << MapSymbols::FOOD; break;

				case MapData::EMPTY:
					ss << MapSymbols::EMPTY; break;
			}
		}
		ss << CRLF;
	}

	log.out(ss.str());
}

snakeDir Game::fixSnakeDirection(const snakeDir newDir)
{
	/* Keeps the current direction if there is no change */
	if (newDir == m_snakeCurrentDir)
		return m_snakeCurrentDir;

	/* keep the same direction to avoid snake turn 180 degress */
	if (m_snakeCurrentDir == Direction::UP && newDir == Direction::DOWN)
		return m_snakeCurrentDir;

	if (m_snakeCurrentDir == Direction::DOWN && newDir == Direction::UP)
		return m_snakeCurrentDir;

	if (m_snakeCurrentDir == Direction::LEFT && newDir == Direction::RIGHT)
		return m_snakeCurrentDir;

	if (m_snakeCurrentDir == Direction::RIGHT && newDir == Direction::LEFT)
		return m_snakeCurrentDir;

	/* Update snake direction if valid */
	switch (newDir)
	{
		case Direction::DOWN:
		case Direction::UP:
		case Direction::LEFT:
		case Direction::RIGHT:
		{
			m_snakeCurrentDir = newDir;
			break;
		}
	}

	return m_snakeCurrentDir;
}

mapData Game::getMapTypeFromCoord(const Coord* c) const
{
	return m_map[c->X][c->Y];
}

Coord Game::getSnakeLastBodyCoord() const
{
	return m_snake[m_snake.size() - 1];
}

void Game::updateGameStatus()
{
	Coord* head = getSnakeHead();

	if (!checkIfSnakeHitsTheWall(head))
	{
		updateMap(head, MapData::SNAKE_HEAD_DEAD);
		setGameStatus(GameStatus::ENDGAME);
		playSoundForDead();
	}

	if (checkIfSnakeBitesItself(head))
	{
		updateMap(head, MapData::SNAKE_HEAD_DEAD);
		setGameStatus(GameStatus::ENDGAME);
		playSoundForDead();
	}

	if (checkIfSankeEatFood(head, &m_foodPos))
	{
		/* Adds a new body part on last position into snake's vector */
		incrementSnake(getSnakeLastBodyCoord());

		/* Set new food position */
		placeFood();

		m_points++;

		playSoundForFood();

		if (m_points >= GamePoints::WIN_GAME)
			setGameStatus(GameStatus::WINGAME);
	}
}

void Game::updateMap(const Coord* c, const mapData type)
{
	m_map[c->X][c->Y] = type;
}

void Game::updateMap(const int coordX, const int coordY, const mapData type)
{
	m_map[coordX][coordY] = type;
}

void Game::moveSnake(const char dir)
{
	/* When game is initialized the direction still not set - do nothing */
	if (dir == CHAR_INIT)
		return;

	size_t size = m_snake.size();

	Coord oldPos = m_snake[0];
	Coord prevPos = m_snake[0];

	for (int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			/* Move head to next position */
			if (dir == Direction::UP)
				m_snake[i].Y--;
			else if (dir == Direction::DOWN)
				m_snake[i].Y++;
			else if (dir == Direction::LEFT)
				m_snake[i].X--;
			else if (dir == Direction::RIGHT)
				m_snake[i].X++;

			updateMap(&m_snake[i], MapData::SNAKE_HEAD);
		}
		else if (i < size)
		{
			/* Snake body follows the head */
			prevPos = m_snake[i];
			m_snake[i] = oldPos;
			updateMap(&oldPos, MapData::SNAKE_BODY);

			oldPos = prevPos;
		}
	}

	/* Set MAP coord from last snake moved body to empty */
	updateMap(&oldPos, MapData::EMPTY);
}

bool Game::isCoordEmpty(const Coord* c) const
{
	return (m_map[c->X][c->Y] == MapData::EMPTY);
}

bool Game::checkIfSnakeHitsTheWall(const Coord* c) const
{
	return isValidCoord(c);
}

bool Game::checkIfSnakeBitesItself(const Coord* c) const
{
	return (getMapTypeFromCoord(c) == MapData::SNAKE_BODY);
}

bool Game::checkIfSankeEatFood(const Coord* snakeHead, const Coord* food) const
{
	return (compareCoord(snakeHead, food));
}

bool Game::isValidCoord(const Coord* c) const
{
	return ((c->Y > MapSize::MIN) && (c->Y < MapSize::MAX_VALID_Y)) && ((c->X > MapSize::MIN) && (c->X < MapSize::MAX_VALID_X));
}

void Game::placeFood()
{
	m_foodPos = getRandomEmptyCoord();
	updateMap(&m_foodPos, MapData::FOOD);
}

Coord Game::getRandomEmptyCoord()
{
	unsigned int counter = 0;

	Coord ret = { getRandomNumber(MapSize::MAX_VALID_X), getRandomNumber(MapSize::MAX_VALID_Y) };

	while (!isCoordEmpty(&ret) && counter < maxLoop)
	{
		ret.X = getRandomNumber(MapSize::MAX_VALID_X);
		ret.Y = getRandomNumber(MapSize::MAX_VALID_Y);
		counter++;
	}

	/* TODO - Think on something here */
	if (counter >= maxLoop)
		setGameStatus(GameStatus::ENDGAME);

	return ret;
}

void Game::printGameInfo()
{
	std::stringstream ss;

	ss << "--------------------------------------------- SNAKE GAME ---------------------------------------------" << CRLF;
	ss << "        Use the ARROW KEYS to control the snake, SPACEBAR to Pause or press ESC to exit the game	     " << CRLF;
	ss << "------------------------------------------------------------------------------------------------------" << CRLF;
	ss << TAB << " Snake Size: " << FORMAT_2_DIGITS << m_snake.size() << " | Points: " << FORMAT_2_DIGITS << m_points
			  << " | Snake Coord: (" << FORMAT_2_DIGITS << m_snake[0].X << "," << FORMAT_2_DIGITS << m_snake[0].Y << ")"
			  << " | Map Size: " << MapSize::MAX_X << "x" << MapSize::MAX_Y << " | Direction: " << getDirectionAsChar(m_snakeCurrentDir) << CRLF;
	ss << "------------------------------------------------------------------------------------------------------" << CRLF;
	ss << CRLF;

	log.out(ss.str(), MapSize::MIN, MapSize::MIN);
}

bool Game::compareCoord(const Coord* a, const Coord* b) const
{
	return ((a->X == b->X) && (a->Y == b->Y));
}

char Game::getDirectionAsChar(const char dir) const
{
	switch (dir)
	{
		case Direction::UP: return 'U';
		case Direction::DOWN: return 'D';
		case Direction::LEFT: return 'L';
		case Direction::RIGHT: return 'R';
		default: return ' ';
	}
}

void Game::setGameStatus(const GameStatus s)
{
	m_status = s;
}

void Game::incrementSnake(Coord c)
{
	m_snake.push_back(c);
}

void Game::playSoundForFood()
{
	PlaySound(TEXT("wav/food.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Game::playSoundForDead()
{
	PlaySound(TEXT("wav/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

Coord* Game::getSnakeHead()
{
	return &m_snake[0];
}

