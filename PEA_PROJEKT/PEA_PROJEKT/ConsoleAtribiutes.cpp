#include "ConsoleAtribiutes.hpp"

unsigned ConsoleAtribiutes::fontColor = WHITE;
unsigned ConsoleAtribiutes::backColor = BLACK;

void ConsoleAtribiutes::setTextColor(unsigned c)
{
	ConsoleAtribiutes::fontColor = c;
}
void ConsoleAtribiutes::setBackColor(unsigned c)
{
	ConsoleAtribiutes::backColor = c;
}

void ConsoleAtribiutes::clearConsole()
{
	#ifdef _WIN32
		system("cls");
	#else
		std::cout << "\033c";
	#endif
}

void ConsoleAtribiutes::updateSettings()
{
	std::string command;
	#ifdef _WIN32
		command = std::string("color ") + std::to_string(fontColor) + std::to_string(backColor);
		system(command.c_str());
	#else
		command = std::string("\033[3") + std::to_string(fontColor) + ";1m";
		std::cout << command;
		command = std::string("\033[4") + std::to_string(backColor) + ";1m";
		std::cout << command;
	#endif 
}

void ConsoleAtribiutes::setDefault()
{
	#ifdef _WIN32
		setTextColor(font);
		setBackColor(back);
		updateSettings();
		//LUB COŚ INNEGO NIE WIEM JAKIE SĄ DOMYŚLNE USTAWIENIA
	#else
		std::cout << "\033[0m";
	#endif
}

void ConsoleAtribiutes::color(const ConsoleColor& font, const ConsoleColor& back)
{
	setTextColor(font);
	setBackColor(back);
	updateSettings();
}