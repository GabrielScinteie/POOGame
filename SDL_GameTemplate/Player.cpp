#include <iostream>
#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Defines.h"
#include "Bomb.h"
#include "Enemy.h"

using namespace std;


SDL_Rect* tempdest;

bool Player::checkcollision(int topA, int rightA, int bottomA, int leftA, int topB, int rightB, int bottomB, int leftB)
{
	int a = 9;//*
	if (bottomA <= topB + a)
	{
		return false;
	}

	if (topA >= bottomB - a)
	{
		return false;
	}

	if (leftA >= rightB - a*2)
	{
		return false;
	}

	if (rightA <= leftB + a)
	{
		return false;
	}

	return true;
}

Player::Player(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

void Player::setTex(const char* path)
{
   texture = TextureManager::LoadTexture(path, renderer);
}


void Player::init()
{
    for (int i = 0; i < 4; i++)
        key_alreadyreleased[i] = 1;
   direction = DEFAULT;
   lastdir = DEFAULT;

   x = y = 64;//*
   height = width = 60;//*
   lastplanted = 0;
   speed = 4;

   srcRect.x = srcRect.y = 0;
   srcRect.w = srcRect.h = 0;

   destRect.x = 64;//*
   destRect.y = 64;//*
   destRect.w = 70;//*
   destRect.h = 70;//*
}

void Player::setdestRect(int x, int y)
{
    destRect.x = x;
    destRect.y = y;
}

void Player::setdirection(KEY_PRESSED x)
{
    direction = x;
}


void Player::handleevent(SDL_Event& event)
{
		for (int i = 0; i < 4; i++) //mereu plec de la ideea ca daca este o tasta apasata atunci in frame-ul actual presupun ca imi pastrez traiectoria acelei taste, daca nu este nici o tasta apasata sta pe loc(daca sunt 2 taste apasate nu conteaza pentru ca va intra pe SDL_KEYDOWN si imi va folosi cea mai recenta tasta apasata
			if (key_alreadyreleased[i] == 0)
			{
				if (i == 0)
				{
					setdirection(UP);
				}
				if (i == 1)
				{
					setdirection(RIGHT);
				}
				if (i == 2)
					setdirection(DOWN);
				if (i == 3)
					setdirection(LEFT);
				break;
			}
			else
				setdirection(DEFAULT);

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				default:
					break;

				case SDLK_SPACE:
				{
					if (event.key.repeat == 0)
					{
						tempdest = new SDL_Rect;
						tempdest->x = (x + 32) / 64 * 64;//32 ptc adun jumatate de latime ca sa fiu sigur ca bomba se pune in patratelul cel mai sugestiv
						tempdest->y = (y + 32) / 64 * 64 ;
						tempdest->w = tempdest->h = 64;

						lastplanted = Bomb::nrBombs;
						Bomb::allBombs[Bomb::nrBombs] = new Bomb("assets/BombAnimation.png", renderer, *tempdest);
						//std::cout << "Bomba " << Bomb::nrBombs << " creata\n";
						Bomb::nrBombs++;

						delete tempdest;
					}

					break;


				}
				case SDLK_ESCAPE:
				{	
					//resetam terenul distrus
					/*for(int i = 0; i < Map::nrTiles; i++)
						if (Map::allTiles[i]->gettype() == 4 && Map::allTiles[i]->getstate() == 1)
						{
							Map::allTiles[i]->setstate(0);
							Map::allTiles[i]->settype(2);
							Map::allTiles[i]->setsrcx(2 * 32);
						}*/

					Game::activated[0] = Game::activated[1] = Game::activated[12] = 0; // Dezactivez mapa si playerul
					Game::activated[2] = Game::activated[4] = 1;//pun meniul
					Game::activated[10] = 1;


					for (int i = 0; i < Map::nrTiles; i++)
						delete Map::allTiles[i];
					Map::nrTiles = 0;

					for (int i = 0; i < Bomb::nrBombs; i++)
						delete Bomb::allBombs[i];
					Bomb::nrBombs = 0;
					for (int i = 0; i < Enemy::nrEnemies; i++)
						delete Enemy::allEnemies[i];
					Enemy::nrEnemies = 0;

				}
				case SDLK_UP:
				{
					setdirection(UP);
					key_alreadyreleased[0] = 0;
					break;
				}
				case SDLK_DOWN:
				{
					setdirection(DOWN);
					key_alreadyreleased[2] = 0;
					break;
				}
				case SDLK_RIGHT:
				{
					setdirection(RIGHT);
					key_alreadyreleased[1] = 0;
					break;
				}
				case SDLK_LEFT:
				{
					setdirection(LEFT);
					key_alreadyreleased[3] = 0;
					break;
				}
			}
		}
		if (event.type == SDL_KEYUP)
		{
			//EX: mergeam dreapta, am apasat tasta jos, incep sa merg in jos(fiind cel mai recent event), ridic tasta dreapta(intru pe acest caz), in acel frame doresc sa imi pastrez directia pe care o aveam inainte
			if (event.key.keysym.sym == SDLK_UP && key_alreadyreleased[0] == 0)
			{
				setdirection(lastdir);
				key_alreadyreleased[0] = 1;
			}
			if (event.key.keysym.sym == SDLK_DOWN && key_alreadyreleased[2] == 0)
			{
				setdirection(lastdir);
				key_alreadyreleased[2] = 1;
			}
			if (event.key.keysym.sym == SDLK_RIGHT && key_alreadyreleased[1] == 0)
			{
				setdirection(lastdir);
			key_alreadyreleased[1] = 1;
			}
			if (event.key.keysym.sym == SDLK_LEFT && key_alreadyreleased[3] == 0)
			{
				setdirection(lastdir);
				key_alreadyreleased[3] = 1;
			}
		}
}

void Player::update(Explosion* exp)
{
	switch (direction)
	{
	case DEFAULT:
		xspeed = yspeed = 0;
		break;
	case UP:
		xspeed = 0;
		yspeed = -1;
		break;
	case RIGHT:
		yspeed = 0;
		xspeed = 1;
		break;
	case DOWN:
		xspeed = 0;
		yspeed = 1;
		break;
	case LEFT:
		yspeed = 0;
		xspeed = -1;
		break;
	default:
		break;
	}
	lastdir = direction;
	// cout << "xspeed: " << xspeed << " yspeed: " << yspeed << '\n';

	x += xspeed * speed;
	y += yspeed * speed;
	//cout << "x: " << x << ' ' << "y: " << y << '\n';
	destRect.x = x;
	destRect.y = y;

	if (destRect.x + destRect.w > LEVEL_WIDTH || destRect.x < 0)
	{
		destRect.x -= xspeed * speed;
		x -= xspeed * speed;
	}


	if (destRect.y + destRect.h > LEVEL_HEIGHT || destRect.y < 0)
	{
		destRect.y -= yspeed * speed;
		y -= yspeed * speed;
	}

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

			collision = checkcollision(y, x + width, y + height, x, toptile, righttile, bottomtile, lefttile);
			if (collision == true)
			{
				//cout << lefttile << ' ' << toptile << ' ' << righttile << ' ' << bottomtile << '\n';
				//cout << x << ' ' << y << ' ' << x + width << ' ' << y + height << '\n';
				break;
			}
		}
	}

	if(collision == 0)
		if (Bomb::nrBombs)
		{
			int bottomtile = Bomb::allBombs[lastplanted]->gety() + 64;
			int toptile = Bomb::allBombs[lastplanted]->gety();
			int lefttile = Bomb::allBombs[lastplanted]->getx();
			int righttile = Bomb::allBombs[lastplanted]->getx() + 64;

			if (Bomb::allBombs[lastplanted]->getexit() == 0 && checkcollision(y, x + width, y + height, x, toptile, righttile, bottomtile, lefttile) == 0)
				Bomb::allBombs[lastplanted]->setexit(1);

			for (int i = 0; i < Bomb::nrBombs; i++)
			{
				bottomtile = Bomb::allBombs[i]->gety() + 64;
				toptile = Bomb::allBombs[i]->gety();
				lefttile = Bomb::allBombs[i]->getx();
				righttile = Bomb::allBombs[i]->getx() + 64;
				//std::cout << "Bomba " << i << " cu exit = " << Bomb::allBombs[i]->getexit() << '\n';
				collision = (Bomb::allBombs[i]->getexit() == 1) && (checkcollision(y, x + width, y + height, x, toptile, righttile, bottomtile, lefttile) == 1);
				if (collision)
				{
					break;
				}
			}
		}
	


	if (collision == 1)
	{
		destRect.x -= xspeed * speed;
		x -= xspeed * speed;

		destRect.y -= yspeed * speed;
		y -= yspeed * speed;
	}

	//for (int i = 0; i < exp->getlg(); i++)
		//for(int j = 0; j < exp->getlt(); j++)
	if ((exp->getfire()[(y + height/2)/ 64][(x + width / 2) / 64] == 1) || (exp->getfire()[y / 64][x / 64] == 1))
		this->init();

}

void Player::draw(SDL_Rect camera)
{
	destRect.x = destRect.x - camera.x;
	destRect.y = destRect.y - camera.y;
    TextureManager::Draw(texture, srcRect, destRect, renderer);
}