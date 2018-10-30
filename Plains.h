#pragma once
#include "Tile.h"
class Plains : public Tile
{
public:
	Plains() {
		moveCost = 1;
		defense = 0;
		type = "Plains";
	};
	~Plains() {};
};