#include "stdafx.h"
#include "MatrixGraph.h"
#ifdef _WIN32
	#include <windows.h>
#endif

using namespace std;

void clearConsole()
{
	#ifdef _WIN32
		system("cls");
	#else
		cout << "\033c";
	#endif
}
string getFileName()
{
	cout << "Podaj nazwe pliku wraz ze sciezka: ";
	string s;
	cin >> s;
	return s;
}
void setRedFont()
{
	#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 0x40);
	#else
		cout << "\033[31;1m";
	#endif
}
void restoreDefaultConsole()
{
	#ifdef _WIN32
		;
	#else
		cout << "\033[0m";
	#endif
}

int main(int argc, char** argv)
{
	if(argc > 1) //testowanie
	{

	}
	else //menu
	{
		MatrixGraph graph;
		char menu;
		do
		{
			clearConsole();
			setRedFont();
			cout << "Projektowanie Efektywnych Algorytmow - Projekt\nProwadzacy: dr Zbigniew Buchalski\nAutorzy: Bartosz Ciesla 209851 Bartosz Kardas 209913\n\n";
			if(graph.getVertexNumber() <= 32)
				graph.output();
			else
			{
				setRedFont();
				cout << "Nie mozna wyswietlic grafu. Graf jest zbyt duzy!\n\n";
				restoreDefaultConsole();
			}
			cout<<"Menu:\n[1] Zaladuj graf z pliku\n[2] Algorytm symulowanego wyzarzania\n[0] Zakoncz\n";
			cin >> menu;
			cin.ignore();
			switch(menu)
			{
				case '1':
					graph.readXml(getFileName().c_str());
				break;
				case '2':
					graph.simulatedAnnealing();
					cin.get();
				break;
				case '0':
				default:
				break;
			}
		}while(menu != '0');
		clearConsole();
	}

	return 0;
}
