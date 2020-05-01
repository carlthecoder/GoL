#include "GoLSim.h"
#include <random>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

void GoLSim::Initialize()
{
	for (size_t y = 0; y < colsize; ++y)
	{
		for (size_t x = 0; x < rowsize; ++x)
		{
			tiles[x][y] = Tile(x, y);
			tiles[x][y].SetAlive(false);
		}
	}

	//runUpdate = false;
	//SetRandomStartingState();
	GosperGlidingGun();
}

void GoLSim::Update()
{
	if (!runUpdate)
	{
		return;
	}

	SDL_Delay(250);

	for (size_t y = 0; y < colsize; ++y)
	{
		for (size_t x = 0; x < rowsize; ++x)
		{
			//CheckSurroundingCells(refTile);
			Tile& refTile { tiles[x][y] };
			auto future = std::async(std::launch::async, &GoLSim::CheckSurroundingCells, this, std::ref(refTile));

			// std::thread and std::async by default copy the parameters to functions.
			// std::ref ensures that the parameter is passed as a reference.

			//std::thread t1(&GoLSim::CheckSurroundingCells, this, std::ref(refTile));
			//t1.join();

			/*auto future = std::async(std::launch::async, [this, x, y]()
			{
				CheckSurroundingCells(tiles[x][y]);
			});*/
		}
	}
}

void GoLSim::Render()
{
	for (size_t y = 0; y < colsize; ++y)
	{
		for (size_t x = 0; x < rowsize; ++x)
		{
			tiles[x][y].Draw();
		}
	}
}

void GoLSim::CheckSurroundingCells(Tile& refTile)
{
	int counter = 0;
	unsigned int xCurrent = refTile.GetX();
	unsigned int yCurrent = refTile.GetY();

	int xLim = 0;
	int yLim = 0;
	int xStart = 0;
	int yStart = 0;

	if ((xCurrent == 0) && (yCurrent == 0))
	{
		xLim = yLim = 2;
		xStart = yStart = 0;
	}
	else if ((xCurrent == 0) && (yCurrent == colsize - 1))
	{
		xLim = yLim = 2;
		xStart = 0;
		yStart = yCurrent - 1;
	}
	else if (xCurrent == 0)
	{
		xLim = 2;
		yLim = 3;
		xStart = 0;
		yStart = yCurrent - 1;
	}
	else if ((xCurrent == rowsize - 1) && (yCurrent == 0))
	{
		xLim = yLim = 2;
		xStart = xCurrent - 1;
		yStart = 0;
	}
	else if ((xCurrent == rowsize - 1) && (yCurrent == colsize - 1))
	{
		xLim = yLim = 2;
		xStart = xCurrent - 1;
		yStart = yCurrent - 1;
	}
	else if (xCurrent == rowsize - 1)
	{
		xLim = 2;
		yLim = 3;
		xStart = xCurrent - 1;
		yStart = yCurrent - 1;
	}
	else if (yCurrent == 0)
	{
		xLim = 3;
		yLim = 2;
		xStart = xCurrent - 1;
		yStart = 0;
	}
	else if (yCurrent == colsize - 1)
	{
		xLim = 3;
		yLim = 2;
		xStart = xCurrent - 1;
		yStart = yCurrent - 1;
	}
	else
	{
		xLim = yLim = 3;
		xStart = xCurrent - 1;
		yStart = yCurrent - 1;
	}

	auto LimX = xStart + xLim;
	auto LimY = yStart + yLim;

	for (int x = xStart; x < LimX; ++x)
	{
		for (int y = yStart; y < LimY; ++y)
		{
			if (tiles[x][y] == refTile)
			{
				continue;
			}
			if (tiles[x][y].IsAlive())
			{
				counter++;
			}
		}
	}

	if (refTile.IsAlive())
	{
		if (counter < 2)
		{
			refTile.SetAlive(false);
		}
		else if (counter > 3)
		{
			refTile.SetAlive(false);
		}
	}
	else if (counter == 3)
	{
		refTile.SetAlive(true);
	}
}

//Any live cell with two or three live neighbors survives.
//Any dead cell with three live neighbors becomes a live cell.
//All other live cells die in the next generation

void GoLSim::SetRandomStartingState()
{
	srand((unsigned int)time(0));
	auto max = 50;
	auto min = 30;
	unsigned int amount = rand() % max + min;

	for (size_t i = 0; i < amount; ++i)
	{
		int x = rand() % rowsize;
		int y = rand() % colsize;

		tiles[x][y].SetAlive(true);
	}
}

void GoLSim::GosperGlidingGun()
{
	tiles[1][5].SetAlive(true);
	tiles[1][6].SetAlive(true);
	tiles[2][5].SetAlive(true);
	tiles[2][6].SetAlive(true);

	tiles[11][5].SetAlive(true);
	tiles[11][6].SetAlive(true);
	tiles[11][7].SetAlive(true);
	tiles[12][4].SetAlive(true);
	tiles[12][8].SetAlive(true);
	tiles[13][3].SetAlive(true);
	tiles[13][9].SetAlive(true);
	tiles[14][3].SetAlive(true);
	tiles[14][9].SetAlive(true);
	tiles[15][6].SetAlive(true);
	tiles[16][4].SetAlive(true);
	tiles[16][8].SetAlive(true);
	tiles[17][5].SetAlive(true);
	tiles[17][6].SetAlive(true);
	tiles[17][7].SetAlive(true);
	tiles[18][6].SetAlive(true);

	tiles[21][5].SetAlive(true);
	tiles[21][4].SetAlive(true);
	tiles[21][3].SetAlive(true);
	tiles[22][5].SetAlive(true);
	tiles[22][4].SetAlive(true);
	tiles[22][3].SetAlive(true);
	tiles[23][2].SetAlive(true);
	tiles[23][6].SetAlive(true);
	tiles[25][2].SetAlive(true);
	tiles[25][6].SetAlive(true);
	tiles[25][1].SetAlive(true);
	tiles[25][7].SetAlive(true);

	tiles[35][2].SetAlive(true);
	tiles[35][3].SetAlive(true);
	tiles[36][2].SetAlive(true);
	tiles[36][3].SetAlive(true);
}