#pragma once
#include "SDL.h"
#include "Explosion.h"

enum KEY_PRESSED { UP, RIGHT, DOWN, LEFT, NUP,NRIGHT,NDOWN,NLEFT, DEFAULT};

class Player
{
public:

   Player() = default;
   Player(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init();

	void update(Explosion* exp);
	void draw(SDL_Rect camera);
	void setdirection(KEY_PRESSED x);
	void setdestRect(int x, int y);
	void handleevent(SDL_Event& x);
	int getx() { return x; }
	int gety() { return y; }
	int getwidth() { return width; }
	int getheight() { return height; }
	int getlastplanted() { return lastplanted; }
	void setlastplanted(int x) { lastplanted = x; }


	bool checkcollision(int topA, int rightA, int bottomA, int leftA, int topB, int rightB, int bottomB, int leftB);

	bool key_alreadyreleased[4];
	KEY_PRESSED direction;
	KEY_PRESSED lastdir;

private:
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	int speed;
	int xspeed, yspeed;
	int x, y;
	int width, height;
	int lastplanted;

};
