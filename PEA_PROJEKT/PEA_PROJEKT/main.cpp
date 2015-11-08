#include "stdafx.h"
#include "MatrixGraph.h"

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
			cout << "Projektowanie Efektywnych Algorytmów - Projekt\nProwadzacy: dr Zbigniew Buchalski\nAutorzy: Bartosz Cieśla 209851 Bartosz Kardas 209913\n\n";
			if(graph.getVertexNumber() <= 32)
				graph.output();
			else
			{
				cout << "Nie można wyświetlić grafu. Graf jest zbyt duży!\n\n";
			}
			cout<<"Menu:\n[1] Załaduj graf z pliku\n[2] Algorytm symulowanego wyżarzania\n[0] Zakończ\n";
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
