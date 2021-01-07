#pragma once
#include "Enemy.h"

class StrongEnemy : public Enemy
{
protected:
	int speed;
public:
	StrongEnemy(const char* textureSheet, SDL_Renderer* renderer, int x, int y, int speed);
	int getspeed() { return speed; }
	void setspeed(int x) { speed = x; }
	void friend initializeEnemiesLvl3(SDL_Renderer* renderer,int speed);
	void Update(Explosion* exp, int nrordine, Player* player);
};

void initializeEnemiesLvl3(SDL_Renderer* renderer,int speed);