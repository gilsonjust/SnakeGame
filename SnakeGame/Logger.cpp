#include "Logger.h"

Logger::Logger()
{
	log.clear();
	showScreenCursor(false);
	setCursorPosition(0, 0);
}

void Logger::out(const std::string& s)
{
	cout << s;
}

void Logger::out(const std::string& s, int x, int y)
{
	setCursorPosition(x, y);
	cout << s;
}

void Logger::appendToLog(const std::string& s)
{
	log << s;
}

void Logger::logToTerminal(int x, int y)
{
	setCursorPosition(x, y);
	std::cout << log.str();
	log.clear();
}

void Logger::clearScreen()
{
	system("cls");
}

void Logger::setCursorPosition(const short x, const short y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/* Switch on/off curson blinking on terminal screen */
void Logger::showScreenCursor(const bool value) const
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = value;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

