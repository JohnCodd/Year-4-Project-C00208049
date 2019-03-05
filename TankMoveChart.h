#pragma once
#include "BaseMoveChart.h"

class TankMoveChart : public BaseMoveChart
{
public:
	TankMoveChart() 
	{
		m_chart[TileTypes::Plains] = 1;
		m_chart[TileTypes::Forest] = 3;
	};
};