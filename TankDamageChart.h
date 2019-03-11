#pragma once
#include "BaseDamageChart.h"

class TankDamageChart : public BaseDamageChart
{
public:
	TankDamageChart()
	{
		m_chart[UnitTypes::Tank] = 50;
	}
};