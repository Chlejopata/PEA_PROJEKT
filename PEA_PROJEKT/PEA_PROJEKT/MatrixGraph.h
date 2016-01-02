#ifndef HEADERS_MATRIXGRAPH_H_
#define HEADERS_MATRIXGRAPH_H_

#include "Edge.h"
#include "Data.hpp"
#include "TabuList.hpp"
#include "TabuArray.hpp"
#include "Specimen.hpp"

class TspNode;

class MatrixGraph
{
public:
	MatrixGraph(uint vertexNumber = 0);
	MatrixGraph(const MatrixGraph &mg);
	MatrixGraph(char* path);
	virtual ~MatrixGraph();

	MatrixGraph & operator =(const MatrixGraph & mg);
	void clone(const MatrixGraph &mg);
	bool readXml(const char* path);
	void writeFile(ofstream &output);
	void generateGraph(uint vertexNumber, bool symmetrical = true);
	void output(bool noColor = false);

	void bruteForce(bool printProgress, bool print);
	uint greedyAlg(vector<uint> &bestRoute);
	Data simulatedAnnealing(uint temperature = 0);
	Data tabuSearch(uint tabuListSize = 5, uint iterations = 0);
	Data genetic(uint populationSize);

	int getValue(uint row, uint col);

	vector<Edge> getEdges(uint vertex);

	uint getVertexNumber();
	uint minimizeCost();

	void printRoute(vector<uint> route, bool noColor = false);
protected:
	bool reserve(uint vNumber = 0);
	void purge();

private:
	static bool rndSeed;
	uint vertexNumber;
	int** matrix;	// macierz

	uint getMatrixAbsMax();
	uint getColumnMaxValue();

	int getLowestInRow(uint row);
	int getLowestInCol(uint col);

	void substractFormRow(uint row, int sub);
	void substractFormCol(uint col, int sub);

	void setRow(uint row, int value = -1);
	void setCol(uint col, int value = -1);
	void setValue(uint row, uint col, int value = -1);

	uint getBestNeighbour(TabuContainer &tabuList, vector<uint> &currentPath);

	vector<Specimen> randomizePopulation(uint numberOfSpecimen);

	long noRepeatDraw(bool* drawn, uint length);
	uint calculateCost(vector<uint> &path);

	static bool nextPermutation(uint *array, uint length);
	static double acceptanceProbability(uint energy, uint newEnergy, uint temperature);
	static void initRand();
};

#endif /* HEADERS_MATRIXGRAPH_H_ */
