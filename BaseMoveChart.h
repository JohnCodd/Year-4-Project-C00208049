#pragma once
#include <iostream>
#include <map>
#include "Forest.h"
#include "Plains.h"

class BaseMoveChart
{
public:
	BaseMoveChart() {};
	~BaseMoveChart() {};
	virtual int const getCost(Tile t) { return m_chart[t]; }
	std::map<Tile, int> m_chart;
};