#pragma once
#include "BaseDamageChart.h"

class BomberDamageChart : public BaseDamageChart
{
public:
	BomberDamageChart()
	{
		m_chart[UnitTypes::Tank] = 70;
	}
};