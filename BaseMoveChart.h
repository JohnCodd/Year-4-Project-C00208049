#pragma once
#include <iostream>
#include <map>
#include "TileTypes.h"

class BaseMoveChart
{
public:
	BaseMoveChart() {};
	~BaseMoveChart() {};
	virtual int getCost(TileTypes t) { return m_chart[t]; }
	std::map<TileTypes, int> m_chart;
};