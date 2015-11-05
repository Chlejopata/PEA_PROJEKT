#ifndef _HEADER_EDGE_H_
#define _HEADER_EDGE_H_

#include "stdafx.h"

class Edge
{
public:
	long begin, end, weight;

	Edge(long begin, long end, long weight)
	{
		this->begin = begin;
		this->end = end;
		this->weight = weight;
	}

	~Edge()
	{
		;
	}

	Edge& operator =(const Edge& argument)
	{
		this->begin = argument.begin;
		this->end = argument.end;
		this->weight = argument.weight;

		return *this;
	}

	bool operator< (Edge const &q) const 
	{ 
		return weight > q.weight;
	}

	bool operator== (Edge const &q) const 
	{ 
		return weight == q.weight; 
	}

	bool operator>(Edge const &q) const 
	{ 
		return weight < q.weight; 
	}

	void output()
	{
		cout << "beg: " << begin << " end: " << end << " weight: " << weight << endl;
	}
};

#endif