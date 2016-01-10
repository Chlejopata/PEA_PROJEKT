#pragma once
#include "stdafx.h"

class MatrixGraph;

class Specimen
{
public:
	typedef Specimen Children2[2];

	enum MutationType
	{
		INVERSION,
		INSERTION,
		DISPLACEMENT,
		TRANSPOSITION
	};

	Specimen();
	Specimen(const Specimen &s);
	// Konstruuje osobnika z istniej¹cej œcie¿ki
	Specimen(const vector<uint> &path);
	// Konstruuje osobnika o podanej d³ugoœci losuj¹c œcie¿kê <0, length)
	Specimen(uint length);
	// Konstruktor przenosz¹cy z obiektu
	Specimen(Specimen&& s);
	// Konstruktor przenosz¹cy z wektora
	Specimen(vector<uint> &&path);

	Specimen& operator=(const Specimen &s);
	// Operator przenosz¹cy z obiektu
	Specimen& operator=(Specimen &&s);
	// Operator przenosz¹cy z wektora
	Specimen& operator=(vector<uint> &&path);

	bool operator< (const Specimen &s) const;
	bool operator== (const Specimen &s) const;
	bool operator> (const Specimen &s) const;

	// Operator krzy¿owania
	static void crossover(const Specimen &p1, const Specimen &p2, Children2 &children);
	// Operator mutacji
	void mutate(MutationType mt = INSERTION);

	vector<uint>& getTrait();
	const vector<uint>& getTrait() const;

	const uint& getCost();
	void setCost(uint _cost);

	// Dokonanie selekcji osobników
	static void makeSelection(vector<Specimen> &population);
	static void makeMutation(vector<Specimen> &population, MutationType mt = INSERTION);
	static void makeCrossover(vector<Specimen> &population);

	static void setMutationChance(double _mutationChance);
	static void setGraph(MatrixGraph* _mg);

	

	friend ostream & operator<< (ostream &os, const Specimen &s);
private:
	vector<uint> trait;
	uint cost;

	static bool rndSeed;
	static default_random_engine randomEngine;
	static uniform_real_distribution<double> distribution;
	static double mutationChance;
	static MatrixGraph* mg;

	void clone(const Specimen &s);
	void setRandomTrait(uint length);

	// Algorytmy krzy¿owania
	static void OX(const Specimen &p1, const Specimen &p2, Children2 &children);

	// Algorytmy mutacji
	void inversion();
	void insertion();
	void displacement();
	void transposition();

	void getRandomIndexes(uint &k1, uint &k2);
	static void getRandomIndexes(uint &k1, uint &k2, uint size);

	static void initRand();
	
};

