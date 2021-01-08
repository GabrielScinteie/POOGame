#include "Explosion.h"
#include "Game.h"
#include "TextureManager.h"
#include <iostream>


Explosion::Explosion(const char* textureSheet, SDL_Renderer* renderer,int x, int y) :GameObject(textureSheet, renderer)
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 64;

	//fire[20][25]
	lungime = x;
	latime = y;
	fire = new int* [lungime];
	for (int i = 0; i < lungime; i++)
		fire[i] = new int[latime];
	firetime = new unsigned int* [lungime];
	for (int i = 0; i < lungime; i++)
		firetime[i] = new unsigned int[latime];

	for (int i = 0; i < lungime; i++)
		for (int j = 0; j < latime; j++)
			firetime[i][j] = fire[i][j] = 0;
	//std::cout << "Totul bine la constructor\n";
};

void Explosion::setfire(int x, int y)
{
	fire[x][y] = 1;
	firetime[x][y] = SDL_GetTicks();
	//std::cout << "Totul bine la setfire: " << x << ' ' << y << '\n';
}

void Explosion::stopfire(int x, int y)
{
	fire[x][y] = 0;
	firetime[x][y] = 0;
	//std::cout << "Totul bine la stopfire\n";
}

Explosion::~Explosion()
{
	if (fire != nullptr)
	{
		for (int i = 0; i < lungime; i++)
			delete fire[i];
		delete[] fire;
		fire = nullptr;
	}
	if (firetime != nullptr)
	{
		for (int i = 0; i < lungime; i++)
			delete firetime[i];
		delete[] firetime;
		firetime = nullptr;
	}

}

SDL_Rect* dest;

void Explosion:: Draw(SDL_Rect camera)
{
	dest = new SDL_Rect;
	dest->w =  dest->h = 64;
	for(int i = 0; i < lungime; i++)
		for(int j = 0; j < latime; j++)
			if (fire[i][j])
			{
				dest->x = j * 64 - camera.x;
				dest->y = i * 64 - camera.y;
				TextureManager::Draw(texture, srcRect, *dest, renderer);
			}
}