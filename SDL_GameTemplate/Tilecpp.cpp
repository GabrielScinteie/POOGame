#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

using namespace std;

Tile::Tile(SDL_Renderer* renderer, int x, int y, int width, int height, int type, char* path)//linia, coloana, latimea, inaltimea
{
	destroyed = 0;
	this->x = x;
	this->y = y;
	this->width = width;//*
	this->height = height;//*
	this->type = type;
	this->renderer = renderer;
	texture = TextureManager::LoadTexture(path, renderer);
	//cout << "type: " << type << '\n';
	dest.x = x * 64;//*
	dest.y = y * 64;//*
	dest.h = dest.w = 64;//*

	src.h = 32;
	src.w = 32;
	src.x = type*32;
	src.y = 0;

	/*
	switch (this->type)
	{
		case 0:
		{
			
			break;
		}
		case 1:
		{
			
			break;
		}
		case 2:
		{
			
			break;
		}
		default:
			break;
	}
	*/
}

void Tile::Draw(SDL_Rect camera)
{
	dest.x = x * 64 - camera.x;
	dest.y = y * 64 - camera.y;
	TextureManager::Draw(texture, src, dest, renderer);
}
