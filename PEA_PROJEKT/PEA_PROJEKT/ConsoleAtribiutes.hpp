#ifndef _CONSOLE_ATRIBIUTES_HPP_
#define _CONSOLE_ATRIBIUTES_HPP_

#include <iostream>

#ifdef _WIN32
#include <windows.h>
enum ConsoleColor
{
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	DARK
};
#else
enum ConsoleColor
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	AQUA,
	WHITE,
	DARK
};
#endif


class ConsoleAtribiutes
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
