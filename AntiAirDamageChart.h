#pragma once
#include "BaseDamageChart.h"

class AntiAirDamageChart : public BaseDamageChart
{
public:
	AntiAirDamageChart()
	{
		m_chart[UnitTypes::Tank] = 30;
		m_chart[UnitTypes::AntiAir] = 30;
		m_chart[UnitTypes::Heli] = 70;
	}
};