#include "stdafx.h"
#include "MatrixGraph.h"
//#include "concol.h"
#include "ConsoleAttributes.hpp"

using namespace std;

string getFileName()
{
	cout << "Podaj nazwe pliku wraz ze sciezka: ";
	string s;
	cin >> s;
	return s;
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
			ConsoleAttributes::setDefault();
			ConsoleAttributes::clearConsole();
			ConsoleAttributes::color(yellow, red);
			cout <<"Projektowanie Efektywnych Algorytmow - Projekt\nProwadzacy: dr Zbigniew Buchalski\nAutorzy: Bartosz Ciesla 209851 Bartosz Kardas 209913\n\n";
			ConsoleAttributes::setDefault();
			if(graph.getVertexNumber() <= 32)
				graph.output();
			else
			{
				ConsoleAttributes::color(red);
				cout << "Nie mozna wyswietlic grafu. Graf jest zbyt duzy!\n\n";
				ConsoleAttributes::setDefault();
			}
			cout<<"\nMenu:\n[1] Zaladuj graf z pliku\n[2] Algorytm symulowanego wyzarzania\n[0] Zakoncz\n";
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
		ConsoleAttributes::clearConsole();
	}

	return 0;
}
