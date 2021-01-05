#pragma once
#include <iostream>
#include "Game.h"


void newgame()
{
	Game::activated[0] = 1;//harta
	Game::activated[1] = 1;//jucator
	Game::activated[2] = 0;//new game
	Game::activated[3] = 0;//new game colorat
	Game::activated[4] = 0;//Quit
	Game::activated[5] = 0;//Quit colorat
}

