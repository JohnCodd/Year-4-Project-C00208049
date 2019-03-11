#pragma once
#include "BaseDamageChart.h"

class HeliDamageChart : public BaseDamageChart
{
public:
	HeliDamageChart() 
	{
		m_chart[UnitTypes::Heli] = 50;
		m_chart[UnitTypes::AntiAir] = 50;
		m_chart[UnitTypes::Tank] = 60;
	}
};