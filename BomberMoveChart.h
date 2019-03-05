#pragma once
#include "BaseMoveChart.h"

class BomberMoveChart : public BaseMoveChart
{
public:
	BomberMoveChart()
	{
		m_chart[TileTypes::Plains] = 1;
		m_chart[TileTypes::Forest] = 1;
	};
};