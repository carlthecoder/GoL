#pragma once
#include "Tile.h"
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

class GoLSim
{
public:
	GoLSim() = default;

	void Initialize();
	void TestingShapes();
	void AnotherGlider();
	void OneMinuteLife();
	void SimpleGlider();
	void GosperGlidingGun();
	void Update();
	void Render();

private:
	unsigned int rows { 200 };
	const unsigned int cols { 300 };
	Tile tiles[300][200];
	bool runUpdate { true };
	std::vector<Tile*> turnonTiles;
	std::vector<Tile*> turnoffTiles;

	void CheckSurroundingCells(Tile* refTile);
	void SetRandomStartingState();
};