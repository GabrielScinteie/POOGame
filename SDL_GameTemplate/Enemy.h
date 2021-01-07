#pragma once
#include "GameObject.h"
#include "Explosion.h"
#include "Player.h"
#include "Game.h"

class Enemy :public GameObject
{
	/*	INHERITED FROM GAME OBJECT
	public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer);
	virtual ~GameObject();

	void virtual Update();
	void virtual Render();

	protected:
		SDL_Texture* texture;
		SDL_Rect srcRect;
		SDL_Rect destRect;
		SDL_Renderer* renderer;
	*/

protected:
	int x, y;
	int ordernumber;//numarul de ordine din vectorul cu inamici
	bool alive = 1;
	int direction;
public:
	static int nrEnemies;
	static Enemy* allEnemies[100];
	Enemy(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	//void setordernumber(int x) { ordernumber = x; }
	//int getordernumber() { return ordernumber; }
	int getx() { return x; }
	int gety() { return y; }
	int getstate() { return alive; }
	virtual int getspeed() { return 0; };
	virtual void setspeed(int x) {};
	void Draw(SDL_Rect camera);
	void virtual Update(Explosion* exp, int nrordine,Player* player);
	void Render() {}
};

void initializeEnemiesLvl1(SDL_Renderer* renderer);
void initializeEnemiesLvl2(SDL_Renderer* renderer);

bool checkcollision(int topA, int rightA, int bottomA, int leftA, int topB, int rightB, int bottomB, int leftB);
