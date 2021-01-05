#include <iostream>
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

Explosion* explosions;
Map* map;
Player *player;
SDL_Event Game::event;
bool Game::activated[100];
SDL_Rect* camera;

Button* NewGame;
Button* NewGame2;
Button* Quit1;
Button* Quit2;



Game::Game(): isRunning(false), window(nullptr), renderer(nullptr)
{
	for(int i = 0; i < 100; i++)
		activated[i] = 0;
	activated[2] = 1;//Newgame
	activated[4] = 1;//Quit
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


	NewGame = new Button("assets/newgame.png", newgame, renderer, src, dest);
	NewGame2 = new Button("assets/newgame2.png", newgame, renderer, src, dest);

	dest.y = height / 2 - dest.h / 2;
	Quit1 = new Button("assets/Quit.png", nullptr, renderer, src, dest);
	Quit2 = new Button("assets/Quit2.png", nullptr, renderer, src, dest);

	player = new Player("assets/Player2.png", renderer);
	player->init();

	map = new Map(renderer);
	map->LoadMap((char*)"assets/Map.txt", 20, 25);

	explosions = new Explosion("assets/Fire.png", renderer, 20, 25);


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
				
				if (event.type == SDL_MOUSEBUTTONDOWN && activated[0] == 0)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					if (NewGame->inside(x, y) == 1)
					{
						NewGame->pressed();
						player->init();
						//enemy->init
						initializeEnemiesLvl1(renderer);

					}

					if (Quit1->inside(x, y) == 1)
					{
						isRunning = false;
					}


				}
			}
		}
}

void Game::update() const
{
	if (activated[1] == 1)
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
			Enemy::allEnemies[i]->Update(explosions, i,player);

		player->update(explosions);

		camera->x = (player->getx() + player->getwidth() / 2) - SCREEN_WIDTH/2;
		camera->y = (player->gety() + player->getheight() / 2) - SCREEN_HEIGHT / 2;

		if (camera->x < 0) { camera->x = 0; }
		if (camera->y < 0) { camera->y = 0; }
		if (camera->x > LEVEL_WIDTH - camera->w) { camera->x = LEVEL_WIDTH - camera->w; }
		if (camera->y > LEVEL_HEIGHT - camera->h) { camera->y = LEVEL_HEIGHT - camera->h; }
	}

	if (activated[0] == 0) // daca jocul nu e inceput si am mouse-ul in interior vreunui buton
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
	if( activated[0] == 1)//daca trebuie sa desenez harta
		map->DrawMap(*camera);
	if (activated[1] == 1)//daca trebuie sa desenez player-ul
	{
		player->draw(*camera);
		for (int i = 0; i < Bomb::nrBombs; i++)
			Bomb::allBombs[i]->draw(*camera);
		explosions->draw(*camera);
		for (int i = 0; i < Enemy::nrEnemies; i++)
			Enemy::allEnemies[i]->Draw(*camera);
	}


	if (activated[2] == 1)
		NewGame->Render();
	if (activated[3] == 1)
		NewGame2->Render();
	if (activated[4] == 1)
		Quit1->Render();
	if (activated[5] == 1)
		Quit2->Render();


	
	SDL_RenderPresent(renderer);

}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete explosions;
	for (int i = 0; i < Map::nrTiles; i++)
		delete Map::allTiles[i];
	for (int i = 0; i < Bomb::nrBombs; i++)
		delete Bomb::allBombs[i];
	for (int i = 0; i < Enemy::nrEnemies; i++)
		delete Enemy::allEnemies[i];
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}

