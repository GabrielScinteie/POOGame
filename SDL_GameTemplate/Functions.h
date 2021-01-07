#pragma once
#include <iostream>
#include "Game.h"


void newgame()
{
	Game::activated[0] = 0;//harta
	Game::activated[1] = 0;//jucator
	Game::activated[2] = 0;//new game
	Game::activated[3] = 0;//new game colorat
	Game::activated[4] = 0;//Quit
	Game::activated[5] = 0;//Quit colorat
	Game::activated[6] = 1;//Lvl1
	Game::activated[7] = 0;//Lvl1Blocat
	Game::activated[8] = 0;//Lvl2
	Game::activated[9] = 1;//Lvl2Blocat
	Game::activated[10] = 0;//PRIMUL MENIU
	Game::activated[12] = 0;//harta usoara
	Game::activated[14] = 0;//Lvl3
	Game::activated[15] = 1;//Lvl3Blocat
}

void level1()
{
	Game::activated[0] = 0;//harta
	Game::activated[1] = 1;//jucator
	Game::activated[2] = 0;//new game
	Game::activated[3] = 0;//new game colorat
	Game::activated[4] = 0;//Quit
	Game::activated[5] = 0;//Quit colorat
	Game::activated[6] = 0;//Lvl1
	Game::activated[7] = 0;//Lvl1Blocat
	Game::activated[8] = 0;//Lvl2
	Game::activated[9] = 0;//Lvl2Blocat
	Game::activated[10] = 0;//PRIMUL MENIU
	Game::activated[11] = 0;//daca trebuie sa scriu YouWin
	Game::activated[12] = 1;//harta usoara
	Game::activated[14] = 0;//Lvl3
	Game::activated[15] = 0;//Lvl3Blocat
}

void level2()
{
	Game::activated[0] = 1;//harta
	Game::activated[1] = 1;//jucator
	Game::activated[2] = 0;//new game
	Game::activated[3] = 0;//new game colorat
	Game::activated[4] = 0;//Quit
	Game::activated[5] = 0;//Quit colorat
	Game::activated[6] = 0;//Lvl1
	Game::activated[7] = 0;//Lvl1Blocat
	Game::activated[8] = 0;//Lvl2
	Game::activated[9] = 0;//Lvl2Blocat
	Game::activated[10] = 0;//PRIMUL MENIU
	Game::activated[11] = 0;//daca trebuie sa scriu YouWin
	Game::activated[12] = 0;//harta usoara
	Game::activated[14] = 0;//Lvl3
	Game::activated[15] = 0;//Lvl3Blocat
}

void level3()
{
	Game::activated[0] = 0;//harta
	Game::activated[1] = 1;//jucator
	Game::activated[2] = 0;//new game
	Game::activated[3] = 0;//new game colorat
	Game::activated[4] = 0;//Quit
	Game::activated[5] = 0;//Quit colorat
	Game::activated[6] = 0;//Lvl1
	Game::activated[7] = 0;//Lvl1Blocat
	Game::activated[8] = 0;//Lvl2
	Game::activated[9] = 0;//Lvl2Blocat
	Game::activated[10] = 0;//PRIMUL MENIU
	Game::activated[11] = 0;//daca trebuie sa scriu YouWin
	Game::activated[12] = 0;//harta usoara
	Game::activated[13] = 1;//harta medie
	Game::activated[14] = 0;//Lvl3
	Game::activated[15] = 0;//Lvl3Blocat
}

