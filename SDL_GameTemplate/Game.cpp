#include <iostream>
#include <fstream>
#include <exception>
#include "Defines.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Button.h"
#include "Tile.h"
#include "Functions.h" //functii butoane
#include "Bomb.h"
#include "Explosion.h"
#include "Enemy.h"
#include "GameObject.h"
#include "StrongEnemy.h"

using namespace std;

Explosion* explosions;
Explosion* explosions0;
Map* map;
Player *player;
SDL_Event Game::event;
bool Game::activated[100];
SDL_Rect* camera;

Button* NewGame;
Button* NewGame2;
Button* Quit1;
Button* Quit2;
Button* Level1;
Button* Level1_Blocked;
Button* Level2;
Button* Level2_Blocked;
Button* Level3;
Button* Level3_Blocked;
Button* YouWin;

GameObject** allObjects;
int nrObjects;
bool firstlevelwon = 0;
bool secondlevelwon = 0;

//fstream AccessFile;

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr)
{
	for (int i = 0; i < 100; i++)
		activated[i] = 0;
	activated[0] = 0;//harta cea mai grea
	activated[1] = 0;//Player
	activated[2] = 1;//Newgame
	activated[4] = 1;//Quit
	activated[6] = 0;//Lvl1
	activated[7] = 0;//Lvl1Blocat
	activated[8] = 0;//Lvl2
	activated[9] = 0;//Lvl2Blocat
	activated[10] = 1; //Daca primul meniu este activat
	activated[11] = 0;//YouWin
	activated[12] = 0;//harta cea mai usoara
	activated[13] = 0;//harta medie
	activated[14] = 0;//Lvl3
	activated[15] = 0;//Lvl3Blocat
}

Game::~Game()
{
	delete map;
	delete player;
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int level_height, int level_width)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != nullptr)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	SDL_Rect src, dest;
	src.h = 0;
	src.w = 0;
	src.x = 0;
	src.y = 0;


	dest.w = width / 3;
	dest.h = height / 5;
	dest.x = width / 2 - dest.w / 2;
	dest.y = height / 4 - dest.h / 2;


	NewGame = new Button("assets/newgame.png", newgame, renderer, src, dest);// activated[2]
	NewGame2 = new Button("assets/newgame2.png", newgame, renderer, src, dest);// activated[3]

	dest.y = height / 2 + dest.h / 2;
	Quit1 = new Button("assets/Quit.png", nullptr, renderer, src, dest);// activated[4]
	Quit2 = new Button("assets/Quit2.png", nullptr, renderer, src, dest);// activated[5]

	src.h = src.w = 64;

	dest.w = dest.h;
	dest.x = width / 2 - dest.w / 2;
	dest.y = height / 4 - dest.h / 2;
	Level1 = new Button("assets/1.png", level1, renderer, src, dest);// activated[6]
	Level1_Blocked = new Button("assets/1blocat.png", nullptr, renderer, src, dest);// activated[7]
	
	dest.y = height / 2 - dest.h / 2;
	Level2 = new Button("assets/2.png", level2, renderer, src, dest);// activated[8]
	Level2_Blocked =  new Button("assets/2blocat.png", nullptr, renderer, src, dest);// activated[9]

	dest.y = height / 4 * 3 - dest.h / 2;
	Level3 = new Button("assets/3.png",level3,renderer,src,dest);
	Level3_Blocked = new Button("assets/3blocat.png", nullptr, renderer, src, dest);


	src.w = 128;
	src.h = 64;
	dest.h = height / 2;
	dest.w = width / 4 * 3;
	dest.x = width / 2 - dest.w/2;
	dest.y = height / 2 - dest.h/2;

	YouWin = new Button("assets/YouWin.png", nullptr, renderer, src, dest);//activated[11]

	player = new Player("assets/Player2.png", renderer);// activated[1]

	map = new Map(renderer);//activated[0]

	explosions = new Explosion("assets/Fire.png", renderer, 20, 25);
	explosions0 = new Explosion("assets/Fire.png", renderer, 7, 7);

	camera = new SDL_Rect{ 0,0,width, height };
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
		if (event.type)
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			if (activated[1] == 1)//daca player-ul este activat
			{
				player->handleevent(event);
			}
			else
			{	//daca nu sunt in interiorul jocului verific doar daca se apasa butoane(verific in update hover-urile)
				
				if (activated[10] == 1) // daca jocul nu e inceput si am mouse-ul in interior vreunui buton
				{

					int x, y;
					SDL_GetMouseState(&x, &y);

					//verific daca mouse-ul este in interiorul butoanelor
					if (NewGame->inside(x, y) == 1)
					{
						activated[2] = 0;
						activated[3] = 1;
					}
					else
					{
						activated[2] = 1;
						activated[3] = 0;
					}

					if (Quit1->inside(x, y) == 1)
					{
						activated[4] = 0;
						activated[5] = 1;
					}
					else
					{
						activated[4] = 1;
						activated[5] = 0;
					}
				}

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && activated[10] == 0)
				{
					Game::activated[0] = 0;//harta cea mai grea
					Game::activated[1] = 0;//player
					Game::activated[2] = 1;//new game
					Game::activated[3] = 0;//new game colorat
					Game::activated[4] = 1;//Quit
					Game::activated[5] = 0;//Quit colorat
					Game::activated[6] = 0;//Lvl1
					Game::activated[7] = 0;//Lvl1Blocat
					Game::activated[8] = 0;//Lvl2
					Game::activated[9] = 0;//Lvl2Blocat
					Game::activated[10] = 1;//PRIMUL MENIU
					Game::activated[12] = 0;//harta cea mai usoara
					Game::activated[13] = 0;//harta medie
					Game::activated[14] = 0;//Lvl3
					Game::activated[15] = 0;//Lvl3Blocat
				}

				if (event.type == SDL_MOUSEBUTTONDOWN && activated[1] == 0)//daca nu sunt in joc
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					if (activated[10] == 0)//daca sunt in al doilea meniu
					{
						if (Level1->inside(x, y) == 1)
						{
							Level1->pressed();
							player->init();
							initializeEnemiesLvl1(renderer);
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							
							map->LoadMap((char*)"assets/Map0.txt", 7, 7);
							
							
						}

						if (Level2->inside(x, y) == 1 && activated[8] == 1)//si am deblocat lvl 2
						{
							Level2->pressed();
							map->LoadMap((char*)"assets/Map.txt", 20, 25);
							player->init();
							initializeEnemiesLvl2(renderer);
						}

						if (Level3->inside(x, y) == 1 && activated[14] == 1)
						{
							Level3->pressed();
							map->LoadMap((char*)"assets/Map.txt", 20, 25);
							player->init();
							initializeEnemiesLvl3(renderer,7);
						}
					}
					else
					{
						if (NewGame->inside(x, y) == 1)
						{
							
							NewGame->pressed();
							SDL_Delay(100);
							if (firstlevelwon == 1)
							{
								Game::activated[8] = 1;
								Game::activated[9] = 0;
							}
							if (secondlevelwon == 1)
							{
								Game::activated[14] = 1;
								Game::activated[15] = 0;
							}
						}

						if (Quit1->inside(x, y) == 1 && activated[10] == 1)
						{
							isRunning = false;
						}

					}
				}
			}
		}
}

void Game::update() const
{
	if (activated[1] == 1)//daca sunt in joc
	{
		if (Enemy::nrEnemies == 0 && activated[0] == 1)//nu mai sunt inamici si sunt in mapa 1
		{
			activated[11] = 1;
		}

		if (Enemy::nrEnemies == 0 && activated[12] == 1)//nu mai sunt inamici si sunt in mapa 1
		{
			activated[11] = 1;
		}

		if (Enemy::nrEnemies == 0 && activated[13] == 1)//nu mai sunt inamici si sunt in mapa 1
		{
			activated[11] = 1;
		}
		
		if (activated[0] == 1)
		{
			for (int i = 0; i < Bomb::nrBombs; i++)
			{
				Bomb::allBombs[i]->Update(explosions);
			}
			for (int i = 0; i < explosions->getlg(); i++)
				for (int j = 0; j < explosions->getlt(); j++)
					if (explosions->getfire()[i][j])//daca este "in flacari" locul respectiv
					{
						if (SDL_GetTicks() - explosions->getfiretime()[i][j] > 250)
							explosions->stopfire(i, j);
					}
			for (int i = 0; i < Enemy::nrEnemies; i++)
				Enemy::allEnemies[i]->Update(explosions, i, player);

			player->update(explosions);
		}
		else
			if (activated[12] == 1)
			{
				for (int i = 0; i < Bomb::nrBombs; i++)
				{
					Bomb::allBombs[i]->Update(explosions0);
				}
				for (int i = 0; i < explosions0->getlg(); i++)
					for (int j = 0; j < explosions0->getlt(); j++)
						if (explosions0->getfire()[i][j])//daca este "in flacari" locul respectiv
						{
							if (SDL_GetTicks() - explosions0->getfiretime()[i][j] > 250)
								explosions0->stopfire(i, j);
						}
				for (int i = 0; i < Enemy::nrEnemies; i++)
					Enemy::allEnemies[i]->Update(explosions0, i, player);

				player->update(explosions0);
			}
			else
				if (activated[13] == 1)
				{
					for (int i = 0; i < Bomb::nrBombs; i++)
					{
						Bomb::allBombs[i]->Update(explosions);
					}
					for (int i = 0; i < explosions->getlg(); i++)
						for (int j = 0; j < explosions->getlt(); j++)
							if (explosions->getfire()[i][j])//daca este "in flacari" locul respectiv
							{
								if (SDL_GetTicks() - explosions->getfiretime()[i][j] > 250)
									explosions->stopfire(i, j);
								
							}
					for (int i = 0; i < Enemy::nrEnemies; i++)
						Enemy::allEnemies[i]->Update(explosions, i, player);

					player->update(explosions);
				}


		

		camera->x = (player->getx() + player->getwidth() / 2) - SCREEN_WIDTH/2;
		camera->y = (player->gety() + player->getheight() / 2) - SCREEN_HEIGHT / 2;

		if (camera->x < 0) { camera->x = 0; }
		if (camera->y < 0) { camera->y = 0; }
		if (camera->x > LEVEL_WIDTH - camera->w) { camera->x = LEVEL_WIDTH - camera->w; }
		if (camera->y > LEVEL_HEIGHT - camera->h) { camera->y = LEVEL_HEIGHT - camera->h; }
	}


	if (activated[1] == 0 && activated[10] == 1) // daca jocul nu e inceput si am mouse-ul in interior vreunui buton
	{
		
		int x, y;
		SDL_GetMouseState(&x, &y);

		//verific daca mouse-ul este in interiorul butoanelor
		if (NewGame->inside(x, y) == 1)	
		{
			activated[2] = 0;
			activated[3] = 1;
		}
		else
		{
			activated[2] = 1;
			activated[3] = 0;
		}

		if (Quit1->inside(x, y) == 1)
		{
			activated[4] = 0;
			activated[5] = 1;
		}
		else
		{
			activated[4] = 1;
			activated[5] = 0;
		}
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer);


	//for(int i = 0; i <= 12; i++)
	//	std::cout << activated[i] << ' ';
	//std::cout << '\n';

	if (activated[1] == 1)//daca sunt in joc <-> playerul este activ
	{
		map->Draw(*camera);
		nrObjects = Bomb::nrBombs + Enemy::nrEnemies;
		allObjects = new GameObject* [nrObjects];
		for (int i = 0; i < nrObjects; i++)
		{
			if (i < Bomb::nrBombs)
			{
				allObjects[i] = Bomb::allBombs[i];
			}
			else
				allObjects[i] = Enemy::allEnemies[i - Bomb::nrBombs];
			allObjects[i]->Draw(*camera);//POLIMORFISM
		}

		player->draw(*camera);

		if (activated[0] == 1)
			explosions->Draw(*camera);
		else
			if (activated[12] == 1)
				explosions0->Draw(*camera);
			else
				if (activated[13] == 1)
					explosions->Draw(*camera);

		delete[] allObjects;
	}

	if (activated[10] == 1)//butoanele din primul meniu
	{
		if (activated[2] == 1)
			NewGame->Render();
		if (activated[3] == 1)
			NewGame2->Render();
		if (activated[4] == 1)
			Quit1->Render();
		if (activated[5] == 1)
			Quit2->Render();
	}

	if (activated[10] == 0)//butoanele din al doilea meniu
	{
		if (activated[6] == 1)
		{
			Level1->Render();
		}
		if (activated[7] == 1)
		{
			Level1_Blocked->Render();
		}


		if (activated[8] == 1)
		{
			Level2->Render();
		}

		if (activated[9] == 1)
		{
			Level2_Blocked->Render();
		}

		if (activated[14] == 1)
		{
			Level3->Render();
		}

		if (activated[15] == 1)
		{
			Level3_Blocked->Render();
		}

	}

	if (activated[11] == 1)//daca am castigat nivelul
	{
		if (activated[0] == 1)//daca sunt in mapa grea
		{
			YouWin->Render();
			for (int i = 0; i <= 15; i++)
				activated[i] = 0;
			activated[2] = activated[4] = activated[10] = 1;

			secondlevelwon = 1;
		}

		if (activated[12] == 1)//daca sunt in mapa usoara
		{
			YouWin->Render();
			for (int i = 0; i <= 15; i++)
				activated[i] = 0;
			activated[2] = activated[4] = activated[10] = 1;

			firstlevelwon = 1;
		}

		if (activated[13] == 1)//daca sunt in mapa usoara
		{
			YouWin->Render();
			for (int i = 0; i <= 15; i++)
				activated[i] = 0;
			activated[2] = activated[4] = activated[10] = 1;
		}

		for (int i = 0; i < Map::nrTiles; i++)
			delete Map::allTiles[i];
		Map::nrTiles = 0;
		for (int i = 0; i < Bomb::nrBombs; i++)
			delete Bomb::allBombs[i];
		//Bomb::allBombs = nullptr; nu facem asta ptc allBombs are dimensiunea fixa de 100
		Bomb::nrBombs = 0;
		for (int i = 0; i < Enemy::nrEnemies; i++)
			delete Enemy::allEnemies[i];
		Enemy::nrEnemies = 0;

		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}
	else
		SDL_RenderPresent(renderer);

}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	if(explosions)
		delete explosions;
	if (explosions0)
		delete explosions0;
	for (int i = 0; i < Map::nrTiles; i++)
		delete Map::allTiles[i];
	for (int i = 0; i < Bomb::nrBombs; i++)
		delete Bomb::allBombs[i];
	for (int i = 0; i < Enemy::nrEnemies; i++)
		delete Enemy::allEnemies[i];
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}

