#include "stdafx.h"
#include "MatrixGraph.h"

using namespace std;

int main(int argc, char** argv)
{
	MatrixGraph mg;
	mg.generateGraph(10, false);
	mg.bruteForce(false, true);
	cout << endl;
	mg.simulatedAnnealing(15000);
	cout << endl;
	cin.get();
	return 0;
}
