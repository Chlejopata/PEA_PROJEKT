#include "stdafx.h"
#include "MatrixGraph.h"
#include "ConsoleAtribiutes.hpp"

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
		srand(time(NULL));
		cout << argv[1] << endl;
		int n = atoi(argv[2]);
		for(int i = 0; i < n; ++i)
		{
			MatrixGraph g(argv[1]);
			g.simulatedAnnealing();
		}
	}
	else //menu
	{
		MatrixGraph graph;
		char menu;
		do
		{
			ConsoleAtribiutes::setDefault();
			ConsoleAtribiutes::clearConsole();
			ConsoleAtribiutes::color(BLUE, RED);
			cout <<"Projektowanie Efektywnych Algorytmow - Projekt\nProwadzacy: dr Zbigniew Buchalski\nAutorzy: Bartosz Ciesla 209851 Bartosz Kardas 209913\n\n";
			ConsoleAtribiutes::setDefault();
			if(graph.getVertexNumber() <= 32)
				graph.output();
			else
			{
				ConsoleAtribiutes::color(RED);
				cout << BLACK << "Nie mozna wyswietlic grafu. Graf jest zbyt duzy!\n\n";
				ConsoleAtribiutes::setDefault();
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
		ConsoleAtribiutes::clearConsole();
	}

	return 0;
}
