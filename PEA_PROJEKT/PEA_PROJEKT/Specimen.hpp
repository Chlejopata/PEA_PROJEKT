#pragma once
#include "stdafx.h"

class Specimen
{
public:
	typedef Specimen Children2[2];
	Specimen();
	Specimen(const Specimen &s);
	// Konstruuje osobnika z istniej¹cej œcie¿ki
	Specimen(const vector<uint> &path);
	// Konstruuje osobnika o podanej d³ugoœci losuj¹c œcie¿kê <0, length)
	Specimen(uint length);
	// Konstruktor przenosz¹cy
	Specimen(Specimen&& s);
	
	Specimen& operator =(const Specimen &s);
	// Operator przenosz¹cy
	Specimen& operator=(Specimen&& s);

	
	static void crossover(const Specimen &p1, const Specimen &p2, Children2 &children);
	void mutate();

	vector<uint>& getTrait();
private:
	vector<uint> trait;
	static bool rndSeed;

	void clone(const Specimen &s);
	void setRandomTrait(uint length);

	static void initRand();
};

