#pragma once
#include "Sdl.h"
#include "GameObject.h"

class Tile: public GameObject
{
	protected:
		int x,y, width, height;//dreptunghiul ce contine hitbox-ul pt coliziuni
		int type;
		bool destroyed;//daca destroyed este 1 inseamna ca acolo a fost teren care a fost distrus, folosim la recuperare
		SDL_Renderer* renderer;
		SDL_Texture* texture;

		SDL_Rect src, dest;
	public:
		Tile() = default;
		Tile(SDL_Renderer* renderer, int x, int y, int width, int height, int type, char* path);
		void Draw(SDL_Rect camera);

		bool getstate() { return destroyed; }
		void setstate(bool x) { destroyed = x; }
		int getx() { return x; }
		int gety() { return y; }
		int getw() { return width; }
		int geth() { return height; }
		int gettype() { return type; }
		void settype(int x) { type = x;}
		void setsrcx(int x) { src.x = x; }
		SDL_Texture* gettexture() { return texture; }
};