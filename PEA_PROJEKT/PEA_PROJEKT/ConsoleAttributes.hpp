#ifndef _CONSOLE_ATRIBIUTES_HPP_
#define _CONSOLE_ATRIBIUTES_HPP_

#include "stdafx.h"

#ifdef _WIN32
#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)
enum ConsoleColor
{
	black = 0,
	//dark_blue = 1,
	//dark_green = 2,
	//dark_aqua, dark_cyan = 3,
	//dark_red = 4,
	//dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	//dark_yellow = 6,
	dark_white = 7,
	//gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};
#else
enum ConsoleColor
{
	black = 0,
	red = 1,
	green = 2,
	yellow = 3,
	blue = 4,
	purple = 5, pink = 5, magenta = 5,
	aqua = 6, cyan = 6,
	white = 7, dark_white = 7,
	//DARK = 8
};
#endif


class ConsoleAttributes
{

public:
	static void clearConsole();
	static void setTextColor(unsigned c);
	static void setBackColor(unsigned c);
	static void color(const ConsoleColor& font, const ConsoleColor& back = (ConsoleColor)backColor);
	static void setDefault();
private:
	static unsigned fontColor, backColor;
	static void updateSettings();

};

#endif
