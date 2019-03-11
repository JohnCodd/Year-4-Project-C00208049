#pragma once
#include "BaseMoveChart.h"

class AntiAirMoveChart : public BaseMoveChart
{
public:
	AntiAirMoveChart()
	{
		m_chart[TileTypes::Plains] = 1;
		m_chart[TileTypes::Forest] = 3;
	};
};