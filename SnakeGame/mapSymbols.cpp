#include "mapSymbols.hpp"

/*
	Initialization of MapSymbols data
	** Horizontal map data has 3 characters to avoid the felling that the snake moves faster on vertical, so it minimizes it;
*/

const mapSymbol MapSymbols::SNAKE_HEAD = " @ ";
const mapSymbol MapSymbols::SNAKE_HEAD_DEAD = " X ";
const mapSymbol MapSymbols::SNAKE_BODY = " o ";
const mapSymbol MapSymbols::FOOD = " f ";
const mapSymbol MapSymbols::EMPTY = "   ";
const mapSymbol MapSymbols::WALL_VERTICAL = " \xBA ";				//  ║
const mapSymbol MapSymbols::WALL_HORIZONTAL = "\xCD\xCD\xCD";		// ═══
const mapSymbol MapSymbols::WALL_TOP_RIGHT_CORNER = "\xCD\xBB ";	// ══╗
const mapSymbol MapSymbols::WALL_TOP_LEFT_CORNER = " \xC9\xCD";		// ╔══
const mapSymbol MapSymbols::WALL_BOTTON_RIGHT_CORNER = "\xCD\xBC ";	// ══╝
const mapSymbol MapSymbols::WALL_BOTTON_LEFT_CORNER = " \xC8\xCD";	// ╚══
