#ifndef HEADERS_TABULIST_H_
#define HEADERS_TABULIST_H_

#include "stdafx.h"

class TabuList
{
public:
	TabuList(uint size, uint tabuTime)
	{
		tabuArray = vector<vector<int>>(size, vector<int>(size, 0));
		this->tabuTime = tabuTime;
	}

	int getTabu(uint first, uint second)
	{
		return tabuArray[first][second];
	}

	void setTabu(uint first, uint second)
	{
		tabuArray[first][second] = tabuTime;
		tabuArray[second][first] = tabuTime;
	}

	void decrementTabu()
	{
		for (auto &row : tabuArray)
		{
			for (auto &col : row)
			{
				if (col > 0)
					--col;
				else if (col < 0)
					col = 0;
			}
		}
	}
private:
	vector<vector<int>> tabuArray;
	uint tabuTime;
};

#endif