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

Specimen::Specimen(vector<uint> &&path)
{
	trait = move(path);
}

Specimen& Specimen::operator=(const Specimen &s)
{
	clone(s);
	return *this;
}

Specimen& Specimen::operator=(Specimen&& s)
{
	trait = move(s.trait);
	return *this;
}

Specimen& Specimen::operator=(vector<uint> &&path)
{
	trait = move(path);
	return *this;
}

void Specimen::crossover(const Specimen &p1, const Specimen &p2, Children2 &children)
{
	OX(p1, p2, children);
}

void Specimen::mutate()
{

}

ostream & operator<< (ostream &os, const Specimen &s) {
	for (auto v : s.getTrait())
		os << v << " ";
	return os;
}

vector<uint>& Specimen::getTrait()
{
	return trait;
}

const vector<uint>& Specimen::getTrait() const
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

void Specimen::OX(const Specimen &p1, const Specimen &p2, Children2 &children)
{
	initRand();
	uint vertexNumber = p1.trait.size();
	auto uintMax = numeric_limits<uint>::max();
	vector<uint> ch1(vertexNumber, uintMax), ch2(vertexNumber, uintMax);
	vector<bool> ch1Contains(vertexNumber, false), ch2Contains(vertexNumber, false);

	// Wylosowanie indeksów
	uint k1 = rand() % vertexNumber, k2 = rand() % (vertexNumber - 1);

	if (k2 == k1)
		++k2;
	if (k2 < k1)
		swap(k1, k2);

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

void Specimen::initRand()
{
	if (!rndSeed)
		srand((unsigned)time(nullptr)), rndSeed = true;
}