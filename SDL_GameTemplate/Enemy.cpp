#include <stdlib.h>
#include "Enemy.h"
#include "TextureManager.h"
#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "Bomb.h"

int Enemy::nrEnemies = 0;
Enemy* Enemy::allEnemies[100];

int dl[] = { 0,1,0,-1 };
int dc[] = { -1,0,1,0 };

Enemy::Enemy(const char* textureSheet, SDL_Renderer* renderer, int x, int y):GameObject(textureSheet,renderer)
{
	direction = rand()%4;
	this->x = x;
	this->y = y;
	srcRect.x = 64;
	srcRect.y = 0;
	srcRect.h = srcRect.w = 64;

	destRect.x = x;
	destRect.y = y;
	destRect.h = destRect.w = 60;
}

void Enemy::Draw(SDL_Rect camera)
{
	destRect.x = x - camera.x;
	destRect.y = y - camera.y;

	TextureManager::Draw(texture,srcRect,destRect,renderer);
}

bool checkcollision(int topA, int rightA, int bottomA, int leftA, int topB, int rightB, int bottomB, int leftB)
{
	int a = 1;
	if (bottomA <= topB + a)
	{
		return false;
	}

	if (topA >= bottomB - a)
	{
		return false;
	}

	if (leftA >= rightB - a)
	{
		return false;
	}

	if (rightA <= leftB + a)
	{
		return false;
	}

	return true;
}

void initializeEnemiesLvl1(SDL_Renderer* renderer)
{
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 4 * 64, 2 * 64);
	Enemy::nrEnemies++;
}

void initializeEnemiesLvl2(SDL_Renderer* renderer)
{
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 11 * 64, 1 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 22 * 64, 1 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 11 * 64, 7 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 7 * 64, 7 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 1 * 64, 12 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 22 * 64, 9 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 16 * 64, 10 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 21 * 64, 15 * 64);
	Enemy::nrEnemies++;
	Enemy::allEnemies[Enemy::nrEnemies] = new Enemy("assets/Enemy.png", renderer, 2 * 64, 18 * 64);
	Enemy::nrEnemies++;
}

void Enemy::Update(Explosion* exp,int nrordine, Player* player)
{
	int speed = 2;
	if (exp->getfire()[y/64][x/64] == 1 || exp ->getfire()[(y+32)/64][(x+32)/64] == 1)
	{
		delete Enemy::allEnemies[nrordine];
		for (int i = nrordine; i < Enemy::nrEnemies - 1; i++)
			Enemy::allEnemies[i] = Enemy::allEnemies[i + 1];
		Enemy::nrEnemies--;
		return;
	}
	else
	{
		int toptile = y;
		int righttile = x + 64;
		int downtile = y + 64;
		int lefttile = x;
		if (checkcollision(player->gety(), player->getx() + player->getwidth(), player->gety() + player->getheight(),
			player->getx(), toptile, righttile, downtile, lefttile))
			player->init();

		x += dl[direction] * speed;
		y += dc[direction] * speed;

		bool collision = false;
		for (int i = 0; i < Map::nrTiles; i++)
		{
			if (Map::allTiles[i]->gettype() >= 0 && Map::allTiles[i]->gettype() <= 3)
			{
				bool collision2 = true;
				int bottomtile = Map::allTiles[i]->gety() * 64 + Map::allTiles[i]->geth();//*
				int toptile = Map::allTiles[i]->gety() * 64;//*
				int lefttile = Map::allTiles[i]->getx() * 64;//*
				int righttile = Map::allTiles[i]->getx() * 64 + Map::allTiles[i]->getw();//*

				collision = checkcollision(y, x + 64, y + 64, x, toptile, righttile, bottomtile, lefttile);
				if (collision == true)
				{
					break;
				}
			}
		}

		if (collision == 0)
			if (Bomb::nrBombs)
			{
				for (int i = 0; i < Bomb::nrBombs; i++)
				{
					downtile = Bomb::allBombs[i]->gety() + 64;
					toptile = Bomb::allBombs[i]->gety();
					lefttile = Bomb::allBombs[i]->getx();
					righttile = Bomb::allBombs[i]->getx() + 64;
					//std::cout << "Bomba " << i << " cu exit = " << Bomb::allBombs[i]->getexit() << '\n';
					collision = (checkcollision(y, x + 64, y + 64, x, toptile, righttile, downtile, lefttile) == 1);
					if (collision == true)
					{
						break;
					}
				}
			}

		if (collision == 0)
			for (int i = 0; i < Enemy::nrEnemies; i++)
			{
				if (i != nrordine)
				{
					downtile = Enemy::allEnemies[i]->gety() + 64;
					toptile = Enemy::allEnemies[i]->gety();
					lefttile = Enemy::allEnemies[i]->getx();
					righttile = Enemy::allEnemies[i]->getx() + 64;
					//std::cout << "Bomba " << i << " cu exit = " << Bomb::allBombs[i]->getexit() << '\n';
					collision = (checkcollision(y, x + 64, y + 64, x, toptile, righttile, downtile, lefttile) == 1);
					if (collision == true)
					{
						break;
					}
				}
			}

		if (collision == true)
		{
			x = x - dl[direction] * speed;
			y = y - dc[direction] * speed;
			direction = rand() % 4;
		}
	}
}