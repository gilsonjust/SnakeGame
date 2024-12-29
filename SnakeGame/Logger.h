#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

#include "Util.hpp"

using std::cout;
using std::endl;

class Logger
{
public:
	Logger();
	void out(const std::string& s);
	void out(const std::string& s, int x, int y);
	void appendToLog(const std::string& s);
	void logToTerminal(int x, int y);
	void clearScreen();
	void setCursorPosition(const short x, const short y);
private:
	void showScreenCursor(const bool value) const;
private:
	std::stringstream log;
};

