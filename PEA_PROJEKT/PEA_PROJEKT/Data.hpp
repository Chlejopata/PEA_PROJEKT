#ifndef HEADERS_DATA_H_
#define HEADERS_DATA_H_

#include "stdafx.h"

class Data
{
public:
	Data(vector<uint> &path = vector<uint>(), uint cost = 0, string results = "", double duration = 0.0)
	{
		this->path = path;
		this->cost = cost;
		this->results = results;
		this->duration = duration;
	}

	vector<uint> path;
	uint cost;
	string results;
	double duration;

	friend ostream & operator<< (ostream &os, const Data &data) {
		return os << data.results;
	}
};

#endif
