#include "Engine.h"
#include "SDL.h"
#include <iostream>
#include <memory>

#undef main

int main()
{
	auto engine{ std::make_unique<Engine>() };

	if (!engine->Initialize("GoL", 1200, 800, false))
	{
		SDL_Log("An error occurred. The engine initialisation failed.\n");
		return -1;
	}

	constexpr float frameTime { 1000 / 60 };
	Uint64 now { SDL_GetPerformanceCounter() };
	Uint64 last { 0 };
	double deltaTime { 0 };

	while (engine->IsRunning())
	{
		last = now;

		engine->HandleEvents();
		engine->Update();
		engine->Render();

		now = SDL_GetPerformanceCounter();
		deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

		if (deltaTime < frameTime)
		{
			SDL_Delay(static_cast<Uint32>(frameTime - deltaTime));
		}
	}

	engine->Destroy();
	return 0;
}