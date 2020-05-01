#pragma once
#include "Tile.h"

class GoLSim
{
public:
	GoLSim() = default;

	void Initialize();
	void GosperGlidingGun();
	void Update();
	void Render();

private:
	Tile tiles[38][25];
	unsigned int colsize { 25 };
	unsigned int rowsize { 38 };
	bool runUpdate { true };

	void CheckSurroundingCells(Tile& refTile);
	void SetRandomStartingState();
};