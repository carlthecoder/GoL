#include "TextureManager.h"
#include "Engine.h"

SDL_Texture* TextureManager::LoadTexture(const char* filepath)
{
	auto tempSurface = IMG_Load(filepath);
	auto texture = SDL_CreateTextureFromSurface(Engine::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::RenderTexture(SDL_Texture * texture, SDL_Rect * src, SDL_Rect * dst)
{
	SDL_RenderCopy(Engine::renderer, texture, src, dst);
}
