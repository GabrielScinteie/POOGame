#pragma once
#include "GameObject.h"
#include "Explosion.h"

class Bomb : public GameObject
{
protected:
	unsigned int animation_number;
	int x, y;
	unsigned int currenttime;
	bool exit;//exit = 1 daca playerului a iesit din raza bombei
public:
	Bomb(const char* textureSheet, SDL_Renderer* renderer, SDL_Rect destRect); 
	void Draw(SDL_Rect camera);

	void setanimation(unsigned int x);
	unsigned int getTime();
	int getx() { return x; }
	int gety() { return y; }
	bool getexit() { return exit; }
	void setexit(int x) { exit = x; }
	void explode(Explosion*);
	void Update(Explosion*);
	void Render() {}

	static int nrBombs;
	static Bomb* allBombs[100];
};