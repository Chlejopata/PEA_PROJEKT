#ifndef HEADERS_TABUARRAY_H_
#define HEADERS_TABUARRAY_H_

#include "stdafx.h"
#include "TabuContainer.hpp"

class TabuArray : public TabuContainer
{
public:
	TabuArray(uint size, uint tabuTime)
	{
		tabuArray = vector<vector<int>>(size, vector<int>(size, 0));
		this->tabuTime = tabuTime;
	}

	bool getTabu(uint first, uint second)
	{
		if (tabuArray[first][second])
			return true;
		return false;
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

	void clear()
	{
		tabuArray.clear();
	}
private:
	vector<vector<int>> tabuArray;
};

#endif