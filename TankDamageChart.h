#pragma once
#include "BaseDamageChart.h"

class TankDamageChart : public BaseDamageChart
{
public:
	TankDamageChart()
	{
		m_chart[UnitTypes::Tank] = 50;
		m_chart[UnitTypes::AntiAir] = 50;
		m_chart[UnitTypes::Heli] = 30;
	}
};