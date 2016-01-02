#include "Specimen.hpp"

bool Specimen::rndSeed = false;

// PUBLIC
Specimen::Specimen()
{
	;
}

Specimen::Specimen(const Specimen &s)
{
	clone(s);
}

Specimen::Specimen(const vector<uint> &path)
{
	trait = path;
}

Specimen::Specimen(uint length)
{
	setRandomTrait(length);
}

Specimen::Specimen(Specimen&& s)
{
	trait = move(s.trait);
}

Specimen& Specimen::operator =(const Specimen &s)
{
	clone(s);
}

Specimen& Specimen::operator=(Specimen&& s)
{
	trait = move(s.trait);
	return *this;
}

void Specimen::crossover(const Specimen &p1, const Specimen &p2, Children2 &children)
{

}

void Specimen::mutate()
{

}

vector<uint>& Specimen::getTrait()
{
	return trait;
}

// PRIVATE

void Specimen::clone(const Specimen &s)
{
	trait = s.trait;
}

void Specimen::setRandomTrait(uint length)
{
	initRand();
	trait.resize(length);

	for (uint i = 0; i < length; ++i)
		trait[i] = i;

	random_shuffle(trait.begin(), trait.end());
}

void Specimen::initRand()
{
	if (!rndSeed)
		srand((unsigned)time(nullptr)), rndSeed = true;
}