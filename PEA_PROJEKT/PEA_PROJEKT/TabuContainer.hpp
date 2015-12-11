#ifndef HEADERS_TABUCONTAINER_H_
#define HEADERS_TABUCONTAINER_H_

#include "stdafx.h"
#include "TabuContainer.hpp"

class TabuContainer
{
public:
	virtual bool getTabu(uint first, uint second) = 0;
	virtual void setTabu(uint first, uint second) = 0;
	virtual void decrementTabu() = 0;
	virtual void clear() = 0;
protected:
	uint tabuTime;
};

#endif