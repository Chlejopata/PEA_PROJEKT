#ifndef HEADERS_TABULIST_H_
#define HEADERS_TABULIST_H_

#include "stdafx.h"
#include "TabuContainer.hpp"
#include <list>
#include <tuple>

class TabuList : public TabuContainer
{
public:
	TabuList(uint tabuTime)
	{
		this->tabuTime = tabuTime;
		listSize = 0;
	}

	bool getTabu(uint first, uint second)
	{
		for (tuple<int, int> &t : tabuList)
		{
			int t1 = get<0>(t), t2 = get<1>(t);
			if ((t1 == first && t2 == second) || (t2 == first && t1 == second))
				return true;
		}
		return false;
	}

	void setTabu(uint first, uint second)
	{
		tabuList.push_front(tuple<int, int>(first, second));
		++listSize;
	}

	void decrementTabu()
	{
		if (listSize > tabuTime)
		{
			tabuList.pop_back();
			--listSize;
		}
	}

	void clear()
	{
		tabuList.clear();
		listSize = 0;
	}
private:
	list<tuple<int, int>> tabuList;
	uint listSize;
};

#endif