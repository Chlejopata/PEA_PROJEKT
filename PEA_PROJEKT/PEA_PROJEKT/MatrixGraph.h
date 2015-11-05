#ifndef HEADERS_MATRIXGRAPH_H_
#define HEADERS_MATRIXGRAPH_H_

#include "Edge.h"

class TspNode;

class MatrixGraph
{
public:
	MatrixGraph(uint vertexNumber = 0);
	MatrixGraph(const MatrixGraph &mg);
	MatrixGraph(ifstream &input);
	virtual ~MatrixGraph();

	MatrixGraph & operator =(const MatrixGraph & mg);
	void clone(const MatrixGraph &mg);
	void readFile(ifstream &input);
	void writeFile(ofstream &output);
	void generateGraph(uint vertexNumber, bool symmetrical = true);
	void output(bool noColor = false);

	void bruteForce(bool printProgress);
	uint greedyAlg(vector<uint> &bestRoute);

	int getValue(uint row, uint col);

	vector<Edge> getEdges(uint vertex);

	uint getVertexNumber();
	uint minimizeCost();

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

	long noRepeatDraw(bool* drawn, uint length);

	static bool nextPermutation(uint *array, uint length);
};

#endif /* HEADERS_MATRIXGRAPH_H_ */
