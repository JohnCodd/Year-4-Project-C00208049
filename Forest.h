#pragma once
#include "Tile.h"
class Forest : public Tile
{
public:
	Forest() {
		moveCost = 3;
		defense = 10;
		type = "Forest";
	};
	~Forest() {};
};