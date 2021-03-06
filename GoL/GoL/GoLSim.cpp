#include "GoLSim.h"


void GoLSim::Initialize()
{
	for (size_t y = 0; y < rows; ++y)
	{
		for (size_t x = 0; x < cols; ++x)
		{
			tiles[x][y] = Tile(x, y);
			tiles[x][y].SetAlive(false);
		}
	}

	TestingShapes();
}

void GoLSim::Update()
{
	if (!runUpdate)
	{
		return;
	}

	SDL_Delay(50);

	turnoffTiles.clear();
	turnonTiles.clear();

	for (size_t y = 0; y < rows; ++y)
	{
		for (size_t x = 0; x < cols; ++x)
		{
			Tile* refTile =  &tiles[x][y];
			CheckSurroundingCells(refTile);

			//auto future = std::async(std::launch::async, &GoLSim::CheckSurroundingCells, this, refTile);
			// std::thread and std::async by default copy the parameters to functions.
			// std::ref ensures that the parameter is passed as a reference.
			//std::thread t1(&GoLSim::CheckSurroundingCells, this, refTile);
			//t1.join();
			//auto future = std::async(std::launch::async, [this, x, y]()
			//{
			//	CheckSurroundingCells(&tiles[x][y]);
			//});
		}
	}

	for (auto tile : turnonTiles)
	{
		tile->SetAlive(true);
	}

	for (auto tile : turnoffTiles)
	{
		tile->SetAlive(false);
	}
}

void GoLSim::Render()
{
	for (size_t y = 0; y < rows; ++y)
	{
		for (size_t x = 0; x < cols; ++x)
		{
			tiles[x][y].Draw();
		}
	}
}

void GoLSim::CheckSurroundingCells(Tile* tile)
{
	int aliveNeighbours = 0;
	unsigned int xCurrent = tile->GetX();
	unsigned int yCurrent = tile->GetY();

	int xLim = 0;
	int yLim = 0;
	int xStart = 0;
	int yStart = 0;

	if ((xCurrent == 0) && (yCurrent == 0))
	{
		xLim = yLim = 2;
		xStart = yStart = 0;
	}
	else if ((xCurrent == 0) && (yCurrent == rows - 1))
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
	else if ((xCurrent == cols - 1) && (yCurrent == 0))
	{
		xLim = yLim = 2;
		xStart = xCurrent - 1;
		yStart = 0;
	}
	else if ((xCurrent == cols - 1) && (yCurrent == rows - 1))
	{
		xLim = yLim = 2;
		xStart = xCurrent - 1;
		yStart = yCurrent - 1;
	}
	else if (xCurrent == cols - 1)
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
	else if (yCurrent == rows - 1)
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
			if (tiles[x][y] == *tile)
			{
				continue;
			}
			if (tiles[x][y].IsAlive())
			{
				aliveNeighbours++;
			}
		}
	}	

	if (!tile->IsAlive())
	{
		if (aliveNeighbours == 3)
		{
			turnonTiles.push_back(tile);
		}
	}
	else
	{
		if (aliveNeighbours < 2)
		{
			turnoffTiles.push_back(tile);
		}
		else if (aliveNeighbours >= 4)
		{
			turnoffTiles.push_back(tile);
 		}
	}

	
}

void GoLSim::SetRandomStartingState()
{
	srand((unsigned int)time(0));
	auto max = 50;
	auto min = 30;
	unsigned int amount = rand() % max + min;

	for (size_t i = 0; i < amount; ++i)
	{
		int x = rand() % cols;
		int y = rand() % rows;

		tiles[x][y].SetAlive(true);
	}
}

void GoLSim::TestingShapes()
{
	//GosperGlidingGun();

	//OneMinuteLife();
}

void GoLSim::AnotherGlider()
{
	tiles[62][28].SetAlive(true);
	tiles[63][28].SetAlive(true);
	tiles[63][29].SetAlive(true);
	tiles[64][27].SetAlive(true);
	tiles[64][29].SetAlive(true);
}

void GoLSim::OneMinuteLife()
{
	tiles[23][26].SetAlive(true);
	tiles[24][25].SetAlive(true);
	tiles[24][28].SetAlive(true);
	tiles[25][24].SetAlive(true);
	tiles[25][25].SetAlive(true);
	tiles[25][27].SetAlive(true);
	tiles[25][28].SetAlive(true);
	tiles[26][25].SetAlive(true);
	tiles[26][27].SetAlive(true);
	tiles[27][26].SetAlive(true);
	tiles[30][25].SetAlive(true);
	tiles[30][26].SetAlive(true);
	tiles[30][27].SetAlive(true);
	tiles[31][26].SetAlive(true);
	tiles[32][26].SetAlive(true);
	tiles[33][25].SetAlive(true);
	tiles[33][26].SetAlive(true);
	//tiles[33][27].SetAlive(true);		
}

void GoLSim::SimpleGlider()
{
	tiles[25][25].SetAlive(true);
	tiles[26][23].SetAlive(true);
	tiles[26][25].SetAlive(true);
	tiles[27][24].SetAlive(true);
	tiles[27][25].SetAlive(true);
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

	tiles[35][3].SetAlive(true);
	tiles[35][4].SetAlive(true);
	tiles[36][3].SetAlive(true);
	tiles[36][4].SetAlive(true);
}