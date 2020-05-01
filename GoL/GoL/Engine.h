#pragma once
#include "GoLSim.h"
#include "Tile.h"
#include "SDL.h"
#include <memory>

class Engine
{
public:
	Engine();
	~Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	bool Initialize(const char* windowTitle, int width, int height, bool fullscreen);
	bool IsRunning() { return running; }
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();

	static SDL_Renderer* renderer;

private:
	bool running { false };
	SDL_Window* window { nullptr };

	std::unique_ptr<GoLSim> golSim;
};