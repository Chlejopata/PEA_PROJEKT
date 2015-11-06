#include "stdafx.h"
#include "MatrixGraph.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << argv[0] << endl;
	MatrixGraph mg("TSPLIB/br17.xml");
	//mg.bruteForce(true, true);
	cout << endl;
	mg.simulatedAnnealing(15000);
	cout << endl;
	cin.get();
	return 0;
}
