#pragma once
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int level_height, int level_width);
	static SDL_Event event;
	void handleEvents();
	void update() const;
	void render() const;
	void clean() const;
	void setisrunning(int x) {isRunning = x;}


	bool running() const { return isRunning;  }
	static bool activated[100];//activated[i] = 1 <-> componenta i este activa
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
