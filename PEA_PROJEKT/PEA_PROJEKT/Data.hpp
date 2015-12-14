#ifndef HEADERS_DATA_H_
#define HEADERS_DATA_H_

#include "stdafx.h"

class Data
{
public:
	Data(const vector<unsigned> &path = vector<unsigned>(), unsigned cost = 0, string results = "", double duration = 0.0)
	{
		this->path = path;
		this->cost = cost;
		this->results = results;
		this->duration = duration;
	}

	vector<unsigned> path;
	unsigned cost;
	string results;
	double duration;

	friend ostream & operator<< (ostream &os, const Data &data) {
		return os << data.results;
	}
};

#endif
