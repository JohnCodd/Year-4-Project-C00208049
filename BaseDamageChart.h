#pragma once
#include <map>
#include <optional>
#include "UnitTypes.h"

class BaseDamageChart
{
public:
	BaseDamageChart() {};
	~BaseDamageChart() {};
	virtual int getDamage(UnitTypes u)
	{
		if (m_chart[u].has_value())
		{
			return m_chart[u].value();
		}
		else
		{
			return 0;
		}
	}
protected:
	std::map<UnitTypes, std::optional<int>> m_chart;
};