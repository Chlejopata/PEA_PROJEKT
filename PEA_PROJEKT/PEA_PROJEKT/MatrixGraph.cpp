#include "stdafx.h"
#include "ConsoleAttributes.hpp"
#include "MatrixGraph.h"

bool MatrixGraph::rndSeed = false;
// PUBLIC

MatrixGraph::MatrixGraph(uint vertexNumber)
{
	this->vertexNumber = 0;
	this->matrix = nullptr;

	// Jeśli ilość wierzchołków nie jest zerem
	if (vertexNumber)
		reserve(vertexNumber);
}

MatrixGraph::MatrixGraph(const MatrixGraph &mg)
{
	matrix = nullptr;
	vertexNumber = 0;
	this->clone(mg);
}

MatrixGraph::MatrixGraph(char* path)
{
	this->vertexNumber = 0;
	this->matrix = nullptr;

	readXml(path);
}

MatrixGraph::~MatrixGraph()
{
	purge();
}

MatrixGraph & MatrixGraph::operator =(const MatrixGraph & mg)
{
	clone(mg);
	return *this;
}

void MatrixGraph::clone(const MatrixGraph &mg)
{
	if (vertexNumber != mg.vertexNumber)
		reserve(mg.vertexNumber);

	for (uint row = 0; row < vertexNumber; row++)
	{
		memcpy(matrix[row], mg.matrix[row], sizeof(int) * vertexNumber);
	}
}

bool MatrixGraph::readXml(const char* path)
{
	char* data = nullptr;
	xml_document<> doc;
	try
	{
		file<> xmlFile(path);
		data = new char[xmlFile.size()];
		memcpy(data, xmlFile.data(), xmlFile.size() * sizeof(char));
	}
	catch (runtime_error e)
	{
		cout << "Nie mozna otworzyc pliku: "<< path << endl;
		if (data)
			delete[] data;
		cin.get();
		cin.ignore();
		return false;
	}

	bool retVal = false;
	doc.parse<0>(data);

	xml_node<>* node = doc.first_node("travellingSalesmanProblemInstance");
	if (node)
	{
		node = node->first_node("graph");
		if (node)
		{
			uint vNum = count_children(node);
			reserve(vNum);

			node = node->first_node("vertex");
			for (uint vertex = 0; node != nullptr; node = node->next_sibling("vertex"), ++vertex)
			{
				xml_node<>* edge = node->first_node("edge");
				for (; edge != nullptr; edge = edge->next_sibling("edge"))
				{
					matrix[vertex][atoi(edge->value())] = int(atof(edge->first_attribute("cost")->value()));
					retVal = true;
				}
			}

			for (uint i = 0; i < vertexNumber; i++)
			{
				matrix[i][i] = -1;
			}
			
		}
	}

	if (data)
		delete[] data;
	return retVal;
}

void MatrixGraph::writeFile(ofstream &output)
{
	if (!output.is_open())
		output.open("output.txt", ios_base::out | ios_base::trunc);

	output << vertexNumber << "\n";	// liczba wierzchołków

	for (uint i = 0; i < vertexNumber; ++i)
	{
		for (uint j = 0; j < vertexNumber; ++j)
		{
			output << matrix[i][j] << " ";
		}
		output << "\n";
	}
}

void MatrixGraph::generateGraph(uint vertexNumber, bool symmetrical)
{
	reserve(vertexNumber);
	if (vertexNumber > 1)
	{
		uint colEnd = vertexNumber;
		uint row = 0;

		for (; row < vertexNumber; row++)
		{
			if (symmetrical)
				colEnd = row + 1;
			for (uint col = 0; col < colEnd; col++)
			{
				if (row != col)
				{
					matrix[row][col] = rand() % (vertexNumber << 1);
					if (symmetrical)
						matrix[col][row] = matrix[row][col];
				}
				else
					matrix[row][col] = -1;
			}
		}
	}
}

void MatrixGraph::output(bool noColor)
{
	const uint columnMaxValue = getColumnMaxValue();
	const uint columnValueWidth = (uint)(ceil(log10(columnMaxValue)) + 1);
	const uint vertIndexWidth = (uint)(ceil(log10(vertexNumber - 1)));

	if (!vertexNumber)
	{
		if (!noColor)
			ConsoleAttributes::color(red);
		cout << "Brak grafu do wyswietlenia!\n\n";
		if (!noColor)
			ConsoleAttributes::setDefault();
	}

	for (uint row = 0; row < vertexNumber; row++)
	{
		if (!noColor)
			ConsoleAttributes::color(white);
		cout.width(vertIndexWidth);
		cout << row << ": ";
		if (!noColor)
			ConsoleAttributes::setDefault();
		for (uint col = 0; col < vertexNumber; col++)
		{
			if (noColor)
			{
				cout.width(columnValueWidth);
				cout << matrix[row][col] << " ";
			}
			else
			{
				if (row == col)
				{
					ConsoleAttributes::color(yellow, red);
					cout.width(columnValueWidth);
					cout << matrix[row][col] << " ";
					ConsoleAttributes::setDefault();
				}
				else
				{
					if (row & 1)
					{
						if (col & 1)
							ConsoleAttributes::color(green, black);
						else
							ConsoleAttributes::color(black, green);
					}
					else
					{
						if (col & 1)
							ConsoleAttributes::color(black, green);
						else
							ConsoleAttributes::color(green, black);
					}
					cout.width(columnValueWidth);
					cout << matrix[row][col] << " ";
					ConsoleAttributes::setDefault();
				}
			}
		}
		cout << endl;
	}
}

void MatrixGraph::bruteForce(bool printProgress, bool print)
{
	uint townNumber = vertexNumber;
	if (!townNumber)
		return;

	if (townNumber >= 20)
		printProgress = false;

	ulong endStep = 2;
	for (uint i = 3; i <= townNumber; ++i)
		endStep *= i;

	ulong div = endStep / 100L;
	if (!div)
		div = 1;
	if (div > 1000000L)
		div = 1000000L;

	bool newDiv = false;
	uint bestWeight = -1, currStep = 0;
	uint *townArray = new uint[townNumber];
	uint *bestRoute = new uint[townNumber];

	// Pierwsza permutacja
	for (uint i = 0; i < townNumber; ++i)
		townArray[i] = i;

	clock_t firstPerm;
	double perms = 0.0;

	clock_t overallTime = clock();
	clock_t startTime = clock();
	do
	{
		++currStep;
		double onePerm;
		if (currStep <= 1000)
			firstPerm = clock() - startTime;

		uint currWeight = matrix[townArray[townNumber - 1]][townArray[0]];
		for (uint i = 0; i < townNumber - 1; ++i)
			currWeight += matrix[townArray[i]][townArray[i + 1]];

		if (currStep <= 1000)
			onePerm = firstPerm / (double)CLOCKS_PER_SEC;

		if (currWeight < bestWeight)
		{
			bestWeight = currWeight;
			memcpy(bestRoute, townArray, townNumber * sizeof(uint));
		}

		if (currStep <= 1000)
		{
			perms += onePerm;
			if (currStep == 1000)
			{
				perms /= 1000.0;
				double factorial = 2;
				for (uint i = 3; i < townNumber; ++i)
					factorial *= i;
				perms *= endStep;
				if (printProgress)
					cout << "Przewidywany czas trwania: " << perms << " sekund\n";
			}
		}

		if (printProgress)
		{
			if (!(currStep % div))
			{
				clock_t endTime = clock() - startTime;
				double ratio = ((double)currStep / (double)endStep) * 100.0;
				double estTime = endTime / (double)CLOCKS_PER_SEC;
				estTime /= (div / (double)(endStep - currStep));

				cout << "\r";
				for (uint i = 0; i < 60; i++)
					cout << " ";
				cout.flush();

				cout << "\rPostep: " << ratio;
				cout << "%, przewidywany czas: " << estTime << " sekund";
				cout.flush();

				if (!newDiv)
				{
					div = (long)((double)div / (endTime / (double)CLOCKS_PER_SEC));
					newDiv = true;
				}
				startTime = clock();
			}
		}
	} while (nextPermutation(townArray, townNumber));

	double duration = (clock() - overallTime) / (double)CLOCKS_PER_SEC;

	if (print)
	{
		cout << "\nDroga:\n";
		for (uint i = 0; i < townNumber; ++i)
		{
			if (i < townNumber)
				cout << bestRoute[i] << " -> ";
		}
		cout << bestRoute[0] << endl;
		cout << "Koszt drogi: " << bestWeight << endl;
		cout << "Calkowity czas trwania: " << duration << " sekund\n";
	}

	delete[] bestRoute;
	delete[] townArray;
}

uint MatrixGraph::greedyAlg(vector<uint> &bestRoute)
{
	priority_queue<Edge> beginBH;
	priority_queue<Edge> currBH;

	uint bestWeight = numeric_limits<unsigned int>::max();
	vector<uint> currRoute(vertexNumber + 1);
	bestRoute.reserve(vertexNumber + 1);
	vector<bool> visited(vertexNumber);

	// Petla sprawdzajaca wyjscie z kazdego wierzcholka
	// Zmieniono na < 1, bo ma sprawdzać tylko 1 cykl
	for (uint towns = 0; towns < 1; ++towns)
	{
		uint nextTown = towns;
		uint currWeight = 0;
		fill(visited.begin(), visited.end(), false);
		vector<Edge> tmpEdges;
		// Petla znajdowania cyklu
		for (uint i = 0; i < vertexNumber - 1; ++i)
		{
			tmpEdges = getEdges(nextTown);
			beginBH = priority_queue<Edge>(tmpEdges.begin(), tmpEdges.end());
			if (i < vertexNumber)
				visited[nextTown] = true;
			// Dodawanie ścieżki
			currRoute[i] = nextTown;

			while (visited[beginBH.top().end])
			{
				beginBH.pop();
			}

			currWeight += beginBH.top().weight;
			nextTown = beginBH.top().end;
		}

		currRoute[vertexNumber - 1] = nextTown;

		// Powrót do miasta startowego, pobranie krawędzi ostatniego miasta
		tmpEdges = getEdges(currRoute[vertexNumber - 1]);
		for (uint i = 0; i < tmpEdges.size(); ++i)
		{
			if (tmpEdges[i].end == towns)
			{
				currWeight += tmpEdges[i].weight;
				currRoute[vertexNumber] = towns;
			}
		}

		if (currWeight < bestWeight)
		{
			bestWeight = currWeight;
			bestRoute = currRoute;
		}
	}

	return bestWeight;
}

Data MatrixGraph::simulatedAnnealing(uint temperature)
{
	clock_t overallTime = clock();
	initRand();
	stringstream results;
	vector<uint> route, bestRoute;
	route.reserve(vertexNumber);
	bestRoute.reserve(vertexNumber);
	uint prevCost = greedyAlg(route), bestCost;
	route.pop_back();
	bestRoute = route;
	bestCost = prevCost;

	if (!temperature)
		temperature = vertexNumber << 10;

	default_random_engine gen(uint(time(nullptr)));
	uniform_real_distribution<double> doubleRnd(0.0, 1.0);

	uint i = 0;
	for (; temperature; --temperature, ++i)
	{
		i %= route.size();
		uint firstIndex = rand() % (route.size());
		uint secondIndex = rand() % (route.size() - 1);
		if (secondIndex >= firstIndex)
			++secondIndex;

		vector<uint> tmpVector(route);
		uint tmp = tmpVector[firstIndex];
		tmpVector[firstIndex] = tmpVector[secondIndex];
		tmpVector[secondIndex] = tmp;

		uint tmpCost = calculateCost(tmpVector);
		if (tmpCost < prevCost)
		{
			route = tmpVector;
			prevCost = tmpCost;
		}
		else
		{
			if (acceptanceProbability(prevCost, tmpCost, temperature) >= doubleRnd(gen))
			{
				route = tmpVector;
				prevCost = tmpCost;
			}
		}

		// Śledzenie najlepszego rozwiązania
		if (prevCost < bestCost)
		{
			bestRoute = route;
			bestCost = prevCost;
		}
	}

	double duration = (clock() - overallTime) / (double)CLOCKS_PER_SEC;
	results << "Koszt drogi: " << bestCost << "\nCalkowity czas trwania: " << duration << " sekund\n";
	return Data(bestRoute, bestCost, results.str(), duration);
	
}

Data MatrixGraph::tabuSearch(uint tabuListSize, uint iterations)
{
	clock_t overallTime = clock();
	initRand();
	stringstream results;
	vector<uint> currentPath, bestPath;
	currentPath.reserve(vertexNumber), bestPath.reserve(vertexNumber);
	//TabuArray tabuList(vertexNumber, tabuListSize);
	TabuList tabuList(tabuListSize);
	uint currentCost = 0, bestCost = 0;
	if (!iterations)
		iterations = vertexNumber << 2;

	//	1 - Create an initial solution(could be created randomly), now call it the current solution.
	for (uint i = 0; i < vertexNumber; ++i)
		currentPath.push_back(i);
	currentCost = calculateCost(currentPath);
	bestPath = currentPath;
	bestCost = currentCost;

	for (uint i = 0; i < iterations; ++i)
	{
		//	2 - Find the best neighbor of the current solution by applying certain moves.
		currentCost = getBestNeighbour(tabuList, currentPath);

		//	3 - If the best neighbor is reached my performing a non - tabu move, accept as the new current solution.
		// else, find another neighbor(best non - tabu neighbour).
		if (currentCost < bestCost) 
		{
			bestPath = currentPath;
			bestCost = currentCost;
		}
	}
	//	4 - If maximum number of iterations are reached(or any other stopping condition), go to 5, else go to 2.
	//	5 - Globally best solution is the best solution we found throughout the iterations.
	double duration = (clock() - overallTime) / (double)CLOCKS_PER_SEC;
	results << "Koszt drogi: " << bestCost << "\nCalkowity czas trwania: " << duration << " sekund\n";
	return Data(bestPath, bestCost, results.str(), duration);
}

int MatrixGraph::getValue(uint row, uint col)
{
	return matrix[row][col];
}

vector<Edge> MatrixGraph::getEdges(uint vertex)
{
	vector<Edge> retVal;
	retVal.reserve(vertexNumber);

	for (uint i = 0; i < vertexNumber; i++)
	{
		if (i != vertex)
		{
			retVal.emplace_back(i, vertex, matrix[i][vertex]);
			retVal.emplace_back(vertex, i, matrix[vertex][i]);
		}
	}

	return retVal;
}

uint MatrixGraph::getVertexNumber()
{
	return vertexNumber;
}

uint MatrixGraph::minimizeCost()
{
	/*cout << "\n----------------------------------------" << endl;
	cout << "BEFORE minimizeCost():\n";
	output();*/
	uint lowerBound = 0;
	// Minimalizacja kosztów w wierszach
	for (uint row = 0; row < vertexNumber; row++)
	{
		int tmp = getLowestInRow(row);
		if (tmp > 0)
		{
			lowerBound += tmp;
			substractFormRow(row, tmp);
		}
	}

	// Minimalizacja kosztów w kolumnach
	for (uint col = 0; col < vertexNumber; col++)
	{
		int tmp = getLowestInCol(col);
		if (tmp > 0)
		{
			lowerBound += tmp;
			substractFormCol(col, tmp);
		}
	}

	/*cout << "\nAFTER minimizeCost():\n";
	output();
	cout <<"lowerBound:"<<lowerBound<<"\n----------------------------------------" <<endl;*/
	return lowerBound;
}

void MatrixGraph::printRoute(vector<uint> route, bool noColor)
{
	if (!noColor)
		ConsoleAttributes::setDefault();
	cout << "\nDroga:\n";
	for (uint i = 0; i < route.size(); ++i)
	{
		if (!noColor)
			ConsoleAttributes::color(green);
		cout << "[" << route[i] << "]";
		if (!noColor)
			ConsoleAttributes::color(white);
		cout << " -(";
		if (i < route.size() - 1)
		{
			if (!noColor)
				ConsoleAttributes::color(blue);
			cout << getValue(i, i + 1);
		}
		else
		{
			if (!noColor)
				ConsoleAttributes::color(blue);
			cout << getValue(i, 0);
		}
		if (!noColor)
			ConsoleAttributes::color(white);
		cout << ")-> ";

	}
	if (!noColor)
		ConsoleAttributes::color(green);
	cout << "[" << route[0] << "]" << endl;
	if (!noColor)
		ConsoleAttributes::setDefault();
}

// PROTECTED
bool MatrixGraph::reserve(uint vNumber)
{
	// Jeśli ilość wierzchołków nie jest zerem
	if (vNumber)
	{
		// Czyszczenie grafu
		purge();

		vertexNumber = vNumber;
		matrix = new int*[vertexNumber];

		int** endLoop = matrix + vertexNumber;
		for (int** i = matrix; i < endLoop; ++i)
		{
			*i = new int[vNumber];
			memset(*i, 0, sizeof(int) * vNumber);
		}

		return true;
	}

	return false;
}

void MatrixGraph::purge()
{
	if (matrix)
	{
		int** endLoop = matrix + vertexNumber;
		for (int** i = matrix; i < endLoop; ++i)
		{
			if (*i)
			{
				delete[] * i;
				*i = nullptr;
			}
		}

		delete[] matrix;
		matrix = nullptr;
	}

	vertexNumber = 0;
}

// PRIVATE
uint MatrixGraph::getMatrixAbsMax()
{
	int retVal = 0;

	int** endOuterLoop = matrix + vertexNumber;
	for (int** i = matrix; i < endOuterLoop; ++i)
	{
		int* endInnerLoop = *i + vertexNumber;
		for (int* j = *i; j < endInnerLoop; ++j)
		{
			if (abs(*j) > retVal)
				retVal = abs(*j);
		}
	}

	return retVal;
}

uint MatrixGraph::getColumnMaxValue()
{
	uint retVal = getMatrixAbsMax() + 1;

	if (retVal < vertexNumber - 1)
		retVal = vertexNumber - 1;

	return retVal;
}

int MatrixGraph::getLowestInRow(uint row)
{
	if (row >= vertexNumber)
	{
		return -1;
	}
	else
	{
		int lowest = numeric_limits<int>::max();
		for (uint col = 0; col < vertexNumber; col++)
		{
			if (matrix[row][col] < lowest && matrix[row][col] >= 0)
				lowest = matrix[row][col];
		}

		if (lowest == numeric_limits<int>::max())
			return -1;
		else
			return lowest;
	}
}

int MatrixGraph::getLowestInCol(uint col)
{
	if (col >= vertexNumber)
	{
		return -1;
	}
	else
	{
		int lowest = numeric_limits<int>::max();
		for (uint row = 0; row < vertexNumber; row++)
		{
			if (matrix[row][col] < lowest && matrix[row][col] >= 0)
				lowest = matrix[row][col];
		}

		if (lowest == numeric_limits<int>::max())
			return -1;
		else
			return lowest;
	}
}

void MatrixGraph::substractFormRow(uint row, int sub)
{
	if (sub > 0)
	{
		for (uint col = 0; col < vertexNumber; col++)
		{
			if (matrix[row][col] >= 0)
				matrix[row][col] -= sub;
		}
	}
}

void MatrixGraph::substractFormCol(uint col, int sub)
{
	if (sub > 0)
	{
		for (uint row = 0; row < vertexNumber; row++)
		{
			if (matrix[row][col] >= 0)
				matrix[row][col] -= sub;
		}
	}
}

void MatrixGraph::setRow(uint row, int value)
{
	for (uint col = 0; col < vertexNumber; col++)
	{
		matrix[row][col] = value;
	}
}

void MatrixGraph::setCol(uint col, int value)
{
	for (uint row = 0; row < vertexNumber; row++)
	{
		matrix[row][col] = value;
	}
}

void MatrixGraph::setValue(uint row, uint col, int value)
{
	if (row < vertexNumber && col < vertexNumber)
		matrix[row][col] = value;
}

uint MatrixGraph::getBestNeighbour(TabuContainer &tabuList, vector<uint> &currentPath)
{
	vector<uint> resultPath = currentPath;
	uint currentCost = calculateCost(currentPath);
	uint resultCost = currentCost;
	bool first = true;
	uint v1 = 0, v2 = 0;

	for (uint row = 1; row < vertexNumber; ++row)
	{
		for (uint col = 2; col < vertexNumber; ++col)
		{
			if (row == col)
				continue;
			vector<uint> newPath(currentPath);
			iter_swap(newPath.begin() + row, newPath.begin() + col);
			uint newCost = calculateCost(newPath);

			if ((newCost < resultCost || first) && !tabuList.getTabu(row, col)) 
			{
				first = false;
				v1 = row;
				v2 = col;
				resultPath = newPath;
				resultCost = newCost;
			}
		}
	}

	if (v1)
	{
		tabuList.decrementTabu();
		tabuList.setTabu(v1, v2);
	}

	currentPath = resultPath;
	return currentCost;
}

long MatrixGraph::noRepeatDraw(bool* drawn, uint length)
{
	uint draw = 0, notDrawn = 0, retVal = 0;

	// Ile liczb jest niewylosowanych
	for (uint i = 0; i < length; ++i)
	{
		if (!drawn[i])
			++notDrawn;
	}

	// Która liczba z niewylosowanych ma być wylosowana
	if (notDrawn)
		draw = rand() % notDrawn;
	else
		return -1;

	for (uint i = 0; i <= draw; ++retVal)
	{
		if (!drawn[retVal])
			++i;
	}

	drawn[--retVal] = true;
	return retVal;
}

uint MatrixGraph::calculateCost(vector<uint> &path)
{
	uint cost = 0;
	for (uint i = 1; i < path.size(); i++)
	{
		cost += getValue(path[i - 1], path[i]);
	}

	if (path.size() > 1)
	{
		cost += getValue(path.back(), path.front());
	}
	return cost;
}

bool MatrixGraph::nextPermutation(uint *array, uint length)
{
	// Znajduje nierosnący ciąg
	if (length == 0)
		return false;
	int i = length - 1;
	while (i > 0 && array[i - 1] >= array[i])
		i--;
	if (i == 0)
		return false;

	// Znajdź następnik pivota
	int j = length - 1;
	while (array[j] <= array[i - 1])
		j--;
	int temp = array[i - 1];
	array[i - 1] = array[j];
	array[j] = temp;

	// Odwróć ciąg
	j = length - 1;
	while (i < j)
	{
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
	return true;
}

double MatrixGraph::acceptanceProbability(uint energy, uint newEnergy, uint temperature)
{
	// If the new solution is better, accept it
	if (newEnergy < energy) {
		return 1.0;
	}
	// If the new solution is worse, calculate an acceptance probability
	return exp(double(energy - newEnergy) / double(temperature));
}

void MatrixGraph::initRand()
{
	// Jeśli random seed nie został zainicjowany
	if (!rndSeed)
	{
		srand((unsigned int)time(NULL));
		rndSeed = true;
	}
}