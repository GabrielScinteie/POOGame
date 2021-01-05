#pragma once
#include <SDL_image.h>
#include <string>
#include "Tile.h"

class Map
{
public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(char* path,int sizeX, int sizeY);
	void DrawMap(SDL_Rect camera);

	static Tile** allTiles;//static ptc la un mom dat va fi doar un nivel activat
	static int nrTiles;//static ptc la un mom dat va fi doar un nivel activat

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;


};