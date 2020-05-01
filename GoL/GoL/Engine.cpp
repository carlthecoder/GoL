#include "Engine.h"
#include <iostream>
#include <thread>
#include <future>

SDL_Renderer* Engine::renderer;

Engine::Engine()
	:
	golSim(std::make_unique<GoLSim>())
{}

Engine::~Engine() { SDL_Log("Engine destroyed"); }

bool Engine::Initialize(const char* windowTitle, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	int flags { 0 };
	if (fullscreen)
	{
		width = 1920;
		height = 1080;
	}

	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (!window)
	{
		SDL_Log("Window creation failed: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
		return false;
	}

	running = true;

	golSim->Initialize();

	return running;
}

void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

void Engine::Update()
{
	auto future = std::async(std::launch::async, &GoLSim::Update, golSim.get());
	//golSim->Update();
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	golSim->Render();

	SDL_RenderPresent(renderer);
}

void Engine::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Log("Window and renderer destroyed");
}