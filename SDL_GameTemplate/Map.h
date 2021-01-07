#pragma once
#include <SDL_image.h>
#include <string>
#include "Tile.h"
#include "GameObject.h"

class Map : public GameObject
{
public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(char* path,int sizeX, int sizeY);
	void Draw(SDL_Rect camera);
	void Render() {};
	static Tile** allTiles;//static ptc la un mom dat va fi doar un nivel activat
	static int nrTiles;//static ptc la un mom dat va fi doar un nivel activat

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;


};