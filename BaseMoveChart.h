#pragma once
#include <iostream>
#include <map>
#include <optional>
#include "TileTypes.h"

class BaseMoveChart
{
public:
	BaseMoveChart() {};
	~BaseMoveChart() {};
	virtual int getCost(TileTypes t) 
	{
		if (m_chart[t].has_value())
		{
			return m_chart[t].value();
		}
		else
		{
			return 99;
		}
	}
protected:
	std::map<TileTypes, std::optional<int>> m_chart;
};