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
	// Konstruktor przenosz¹cy z obiektu
	Specimen(Specimen&& s);
	// Konstruktor przenosz¹cy z wektora
	Specimen(vector<uint> &&path);

	Specimen& operator=(const Specimen &s);
	// Operator przenosz¹cy z obiektu
	Specimen& operator=(Specimen &&s);
	// Operator przenosz¹cy z wektora
	Specimen& operator=(vector<uint> &&path);

	// Operator krzy¿owania
	static void crossover(const Specimen &p1, const Specimen &p2, Children2 &children);
	// Operator mutacji
	void mutate();

	vector<uint>& getTrait();
	const vector<uint>& getTrait() const;

	friend ostream & operator<< (ostream &os, const Specimen &s);
private:
	vector<uint> trait;
	static bool rndSeed;

	void clone(const Specimen &s);
	void setRandomTrait(uint length);

	// Krzy¿owania
	static void OX(const Specimen &p1, const Specimen &p2, Children2 &children);

	static void initRand();
};

