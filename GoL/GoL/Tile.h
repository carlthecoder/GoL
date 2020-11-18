#pragma once
#include "SDL.h"

class Tile
{
public:
	Tile(int x = 0, int y = 0, int tilesize = 8);
	~Tile() = default;
	Tile(const Tile&) = default;
	Tile& operator=(const Tile& other)
	{
		texture = other.texture;
		dst = other.dst;
		src = other.src;
		xPos = other.xPos;
		yPos = other.yPos;
		return *this;
	}

	bool operator==(const Tile& other)
	{
		bool same = (xPos == other.xPos) && (yPos == other.yPos);
		return same;
	}	

	int GetX() { return xPos; }
	void SetX(int x) { xPos = x; };

	int GetY() { return yPos; }
	void SetY(int y) { yPos = y; }

	bool IsAlive() { return canRender; }
	void SetAlive(bool allowed) { if (canRender != allowed) canRender = allowed; }

	unsigned int GetTileSize() { return tileSize; }
	void SetTileSize(unsigned int tilesize) { tileSize = tilesize; }
	
	void Draw();

private:
	unsigned int tileSize;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Texture* texture;

	int xPos;
	int yPos;
	bool canRender { true };
};