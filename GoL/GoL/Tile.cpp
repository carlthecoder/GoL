#include "Engine.h"
#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(int x, int y, int tilesize)
	:
	tileSize(tilesize)
{
	auto surface = SDL_CreateRGBSurface(0, tileSize, tileSize, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, 200, 240, 240));
	texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);
	SDL_FreeSurface(surface);

	xPos = x;
	yPos = y;

	src.x = 0;
	src.y = 0;
	src.w = tileSize;
	src.h = tileSize;

	dst.x = 0;
	dst.y = 0;
	dst.w = tileSize;
	dst.h = tileSize;
}

void Tile::Draw()
{
	dst.x = xPos * tileSize;
	dst.y = yPos * tileSize;

	if (canRender)
	{
		TextureManager::RenderTexture(texture, &src, &dst);
	}	
}
