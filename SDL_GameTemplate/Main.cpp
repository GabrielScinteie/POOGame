//Using SDL and standard IO
#include <exception>
#include <iostream>
#include "Game.h"
#include <SDL.h>
#include "Defines.h"
//Screen dimension constants


int main(int argc, char* args[])
{
	const int fps = 60;
	// max time between frames
	const int frameDelay = 1000 / fps;
	Game *game = new Game();

	game->init("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false,LEVEL_HEIGHT,LEVEL_WIDTH);

	while (game->running())
	{
		Uint32 frameStart;

		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		const int frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	return 0;
}