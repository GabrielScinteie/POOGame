#include <iostream>
#include "Bomb.h"
#include "TextureManager.h"
#include "Tile.h"
#include "Map.h"
#include "Explosion.h"
#include "Player.h"
#include "Game.h"

Bomb* Bomb::allBombs[100];
int Bomb::nrBombs = 0;

Bomb::Bomb(const char* textureSheet, SDL_Renderer* renderer, SDL_Rect destRect) : GameObject(textureSheet, renderer)
{
	exit = 0;
	this -> destRect = destRect;
	x = destRect.x;
	y = destRect.y;
	//std::cout << "Bomb : " << x << ' ' << y << '\n';
	currenttime = SDL_GetTicks();
	animation_number = 0;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcRect.h = 256;

}

void Bomb::setanimation(unsigned int x)
{
	animation_number = x;
}

unsigned int Bomb::getTime()
{
	return currenttime;
}

int movx[] = {0,1,0,-1};
int movy[] = { -1,0,1,0 };

void Bomb::explode(Explosion* exp)
{
	int lg,xlovit,ylovit;
	bool blocked;

	exp->setfire(y/64,x/64);

	for (int k = 0; k < 4; k++)
	{
		blocked = 0;
		for (lg = 1; lg <= 2 && blocked == 0; lg++)
		{

			xlovit = x + lg * 64 * movx[k];
			ylovit = y + lg * 64 * movy[k];

			for (int i = 0; i < Map::nrTiles; i++)
				if (Map::allTiles[i]->gettype() == 2 && Map::allTiles[i]->getx() * 64 == xlovit && 
					Map::allTiles[i]->gety() * 64 == ylovit)//pereti destructibili
				{
					exp->setfire(ylovit/ 64, xlovit / 64);
					Map::allTiles[i]->setstate(1);//perete distrus
					Map::allTiles[i]->settype(4);//iarba
					Map::allTiles[i]->setsrcx(4 * 32);//setez textura
					
					blocked = 1;
					break;
				}
				else
					if ((Map::allTiles[i]->gettype() == 1 || Map::allTiles[i]->gettype() == 0 || 
						Map::allTiles[i]->gettype() == 3) && Map::allTiles[i]->getx() * 64 == xlovit && Map::allTiles[i]->gety() * 64 == ylovit)
					{
						
						blocked = 1;
					}
					else
						if (Map::allTiles[i]->gettype() == 4 && Map::allTiles[i]->getx() * 64 == xlovit && Map::allTiles[i]->gety() * 64 == ylovit)
						{
							exp->setfire(ylovit/64, xlovit / 64);
						}
		}
	}
}



void Bomb::Update(Explosion* exp)
{
	for (int i = 0; i < Bomb::nrBombs; i++)
	{
		if ((SDL_GetTicks() - Bomb::allBombs[i]->getTime()) / 1000 >= 3 || exp->getfire()[Bomb::allBombs[i]->gety()/64][Bomb::allBombs[i]->getx()/64] == 1)
		{
			Bomb::allBombs[i]->explode(exp);
			//delete Bomb::allBombs[i];
			for (int j = i; j < Bomb::nrBombs - 1; j++)
				Bomb::allBombs[j] = Bomb::allBombs[j + 1];
			Bomb::nrBombs--;

		}
		else
		{
			Bomb::allBombs[i]->setanimation((SDL_GetTicks() - Bomb::allBombs[i]->getTime()) / 1000);
		}
	}
		
}

void Bomb::Draw(SDL_Rect camera)
{
	destRect.x = x - camera.x;
	destRect.y = y - camera.y;
	srcRect.x = animation_number * 256;
	TextureManager::Draw(texture,srcRect,destRect,renderer);
}