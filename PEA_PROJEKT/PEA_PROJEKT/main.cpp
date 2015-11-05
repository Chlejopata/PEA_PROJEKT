#include "stdafx.h"
#include "MatrixGraph.h"

using namespace std;

int main(int argc, char** argv)
{
	ifstream ifs("2.txt", ios_base::in);
	MatrixGraph mg(ifs);
	//mg.generateGraph(10, false);
	mg.bruteForce(false, true);
	cout << endl;
	mg.simulatedAnnealing(1000);
	cout << endl;
	cin.get();
	return 0;
}
