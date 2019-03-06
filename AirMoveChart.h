#pragma once
#include "BaseMoveChart.h"

class AirMoveChart : public BaseMoveChart
{
public:
	AirMoveChart()
	{
		m_chart[TileTypes::Plains] = 1;
		m_chart[TileTypes::Forest] = 1;
		m_chart[TileTypes::Sea] = 1;
	};
};