#include <fstream>
#include <string>
#include <iostream>
#include <SDL.h>
#include "Tile.h"
#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include <exception>

using namespace std;

Tile** Map:: allTiles;
int Map:: nrTiles;

Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	src.x = 0;
	src.y = 0;
	src.w = 0;
	src.h = 0;

	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

	nrTiles = 0;
	allTiles = new Tile*[500];//20 * 25 = 500 nr maxim de tiles

}

Map::~Map()
{
	delete[] allTiles;
}

void Map::LoadMap(char* path, int sizeX, int sizeY)
{
	char tile;
	fstream mapFile;
	//mapFile.open(path);
	try {
		mapFile.open(path);
		if (!mapFile)
			throw "Eroare deschidere fisier harta\n";
	}

	catch (const char* error)
	{
		std::cout << error << '\n';
	}

	for (int row = 0; row < sizeX; row++)
	{
		for (int column = 0; column < sizeY; column++)
		{
			mapFile.get(tile);
			Tile* temp = new Tile(renderer,column,row,64,64, tile - '0', (char*)"assets/Tiles.png");
			allTiles[nrTiles] = temp;
			nrTiles++;
			mapFile.ignore();
		}
		mapFile.get();
	}

	mapFile.close();
}

void Map::Draw(SDL_Rect camera)
{

	for (int i = 0; i < nrTiles; i++)
	{
		allTiles[i] -> Draw(camera);
	}
}
