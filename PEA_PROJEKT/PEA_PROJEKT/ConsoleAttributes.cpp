#include "ConsoleAttributes.hpp"

unsigned ConsoleAttributes::fontColor = dark_white;
unsigned ConsoleAttributes::backColor = black;

void ConsoleAttributes::setTextColor(unsigned c)
{
	ConsoleAttributes::fontColor = c;
}
void ConsoleAttributes::setBackColor(unsigned c)
{
	ConsoleAttributes::backColor = c;
}

void ConsoleAttributes::clearConsole()
{
	#ifdef _WIN32
		system("cls");
	#else
		std::cout << "\033c";
	#endif
}

void ConsoleAttributes::updateSettings()
{
	std::string command;
	#ifdef _WIN32
		fontColor &= 0xf; backColor &= 0xf;
		unsigned short wAttributes = ((unsigned)backColor << 4) | (unsigned)fontColor;
		SetConsoleTextAttribute(std_con_out, wAttributes);
	#else
		command = std::string("\033[3") + std::to_string(fontColor) + ";1m";
		std::cout << command;
		command = std::string("\033[4") + std::to_string(backColor) + ";1m";
		std::cout << command;
	#endif 
}

void ConsoleAttributes::setDefault()
{
	#ifdef _WIN32
		setTextColor(dark_white);
		setBackColor(black);
		updateSettings();
	#else
		std::cout << "\033[0m";
	#endif
}

void ConsoleAttributes::color(const ConsoleColor& font, const ConsoleColor& back)
{
	setTextColor(font);
	setBackColor(back);
	updateSettings();
}

/*
#if defined(_INC_OSTREAM)||defined(_IOSTREAM_)
ostream& operator<<(ostream& os, ConsoleColor c)
{
	os.flush();
	ConsoleAttributes::color(c);
	return os;
}
#endif

#if defined(_INC_ISTREAM)||defined(_IOSTREAM_)
istream& operator>>(istream& is, ConsoleColor c)
{
	cout.flush(); ConsoleAttributes::color(c); return is;
}
#endif
*/