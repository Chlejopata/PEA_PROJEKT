#include "Specimen.hpp"
#include "MatrixGraph.h"


bool Specimen::rndSeed = false;
default_random_engine Specimen::randomEngine = default_random_engine();
uniform_real_distribution<double> Specimen::distribution = uniform_real_distribution<double>(0.0, 1.0);
double Specimen::mutationChance = 0.0;
MatrixGraph* Specimen::mg = nullptr;

// PUBLIC
Specimen::Specimen()
{
	cost = numeric_limits<uint>::max();
}

Specimen::Specimen(const Specimen &s)
{
	clone(s);
}

Specimen::Specimen(const vector<uint> &path)
{
	cost = numeric_limits<uint>::max();
	trait = path;
}

Specimen::Specimen(uint length)
{
	cost = numeric_limits<uint>::max();
	setRandomTrait(length);
}

Specimen::Specimen(Specimen&& s)
{
	cost = s.cost;
	trait = move(s.trait);
}

Specimen::Specimen(vector<uint> &&path)
{
	cost = numeric_limits<uint>::max();
	trait = move(path);
}

Specimen& Specimen::operator=(const Specimen &s)
{
	clone(s);
	return *this;
}

Specimen& Specimen::operator=(Specimen&& s)
{
	cost = s.cost;
	trait = move(s.trait);
	return *this;
}

Specimen& Specimen::operator=(vector<uint> &&path)
{
	cost = numeric_limits<uint>::max();
	trait = move(path);
	return *this;
}

void Specimen::crossover(const Specimen &p1, const Specimen &p2, Children2 &children)
{
	OX(p1, p2, children);
}

void Specimen::mutate(MutationType mt)
{
	switch (mt)
	{
	case Specimen::INVERSION:
		inversion();
		break;
	case Specimen::INSERTION:
		insertion();
		break;
	case Specimen::DISPLACEMENT:
		displacement();
		break;
	case Specimen::TRANSPOSITION:
		transposition();
		break;
	default:
		break;
	}
}

vector<uint>& Specimen::getTrait()
{
	return trait;
}

const vector<uint>& Specimen::getTrait() const
{
	return trait;
}

const uint& Specimen::getCost()
{
	if (mg && cost == numeric_limits<uint>::max())
		cost = mg->calculateCost(trait);
	return cost;
}

void Specimen::setCost(uint _cost)
{
	cost = _cost;
}

void Specimen::makeSelection(vector<Specimen> &population)
{

}

void Specimen::makeMutation(vector<Specimen> &population, MutationType mt)
{
	for (auto &specimen : population)
	{
		if (distribution(randomEngine) <= mutationChance)
			specimen.mutate(mt);
	}
}

void Specimen::makeCrossover(vector<Specimen> &population)
{

}

void Specimen::setMutationChance(double _mutationChance)
{
	mutationChance = _mutationChance;

	if (mutationChance > 1.0)
		mutationChance = 1.0;
	else if (mutationChance < 0.0)
		mutationChance = 0.0;
}

void Specimen::setGraph(MatrixGraph* _mg)
{
	mg = _mg;
}

ostream & operator<< (ostream &os, const Specimen &s) 
{
	for (auto v : s.getTrait())
		os << v << " ";
	return os;
}

// PRIVATE

void Specimen::clone(const Specimen &s)
{
	trait = s.trait;
	cost = s.cost;
}

void Specimen::setRandomTrait(uint length)
{
	initRand();
	trait.resize(length);

	for (uint i = 0; i < length; ++i)
		trait[i] = i;

	random_shuffle(trait.begin(), trait.end());
}

void Specimen::OX(const Specimen &p1, const Specimen &p2, Children2 &children)
{
	uint vertexNumber = p1.trait.size();
	auto uintMax = numeric_limits<uint>::max();
	vector<uint> ch1(vertexNumber, uintMax), ch2(vertexNumber, uintMax);
	vector<bool> ch1Contains(vertexNumber, false), ch2Contains(vertexNumber, false);

	// Wylosowanie indeksów
	uint k1, k2;
	getRandomIndexes(k1, k2, vertexNumber);

	// Kopiowanie sekcji dopasowania
	copy(p1.trait.begin() + k1, p1.trait.begin() + k2, ch2.begin() + k1);
	copy(p2.trait.begin() + k1, p2.trait.begin() + k2, ch1.begin() + k1);

	// Zape³nianie tablicy zawartoœci (czy œcie¿ka zawiera ju¿ dany wierzcho³ek w trasie)
	uint i = k1;
	for (; i < k2; ++i)
	{
		if (ch1[i] != uintMax)
			ch1Contains[i] = true;
		if (ch2[i] != uintMax)
			ch2Contains[i] = true;
	}

	uint ch1Pos = k2, ch2Pos = k2;
	for (;; i = ((i + 1) % vertexNumber))
	{
		// Jeœli pierwsze dziecko nie zawiera wierzcho³ka z drugiego rodzica
		if (!ch1Contains[p2.trait[i]])
		{
			ch1Contains[p2.trait[i]] = true;
			ch1[ch1Pos] = p2.trait[i];
			ch1Pos = (ch1Pos + 1) % vertexNumber;
		}

		// Jeœli drugie dziecko nie zawiera wierzcho³ka z pierwszego rodzica
		if (!ch2Contains[p1.trait[i]])
		{
			ch2Contains[p1.trait[i]] = true;
			ch2[ch2Pos] = p1.trait[i];
			ch2Pos = (ch2Pos + 1) % vertexNumber;
		}

		if (ch1Pos == k1 && ch2Pos == k1)
			break;
	}

	children[0] = move(ch1);
	children[1] = move(ch2);
}

void Specimen::inversion()
{
	// Wylosowanie indeksów
	uint k1, k2;
	getRandomIndexes(k1, k2);

	for (; k1 != k2 && k1 < k2; ++k1, --k2)
		swap(trait[k1], trait[k2]);
}

void Specimen::insertion()
{
	// Wylosowanie indeksów
	uint k1, k2;
	getRandomIndexes(k1, k2);

	// Losowa zamiana, ¿eby nie braæ zawsze mniejszego
	if (rand() % 2)
		swap(k1, k2);

	auto tmp = trait[k1];

	trait.erase(trait.begin() + k1);
	trait.insert(trait.begin() + k2, tmp);
}

void Specimen::displacement()
{
	// Wylosowanie indeksów
	uint k1, k2;
	getRandomIndexes(k1, k2);

	swap(trait[k1], trait[k2]);
}

void Specimen::transposition()
{
	// Wylosowanie indeksów
	uint k1, k2;
	getRandomIndexes(k1, k2);

	swap(trait[k1], trait[k2]);
}

void Specimen::getRandomIndexes(uint &k1, uint &k2)
{
	getRandomIndexes(k1, k2, trait.size());
}

void Specimen::getRandomIndexes(uint &k1, uint &k2, uint size)
{
	initRand();
	// Wylosowanie indeksów
	k1 = rand() % size, k2 = rand() % (size - 1);

	if (k2 == k1)
		++k2;
	if (k2 < k1)
		swap(k1, k2);
}

void Specimen::initRand()
{
	if (!rndSeed)
		srand((unsigned)time(nullptr)), rndSeed = true;
}