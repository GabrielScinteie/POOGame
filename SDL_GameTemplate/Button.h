#pragma once
#include "GameObject.h"
#include "TextureManager.h"

class Button : public GameObject
{
public:
	Button(const char* textureSheet, void (*callback) (), SDL_Renderer* renderer, SDL_Rect _srcrec, SDL_Rect _destrec);
	void Render();
	void pressed();
	bool inside(int x, int y);
	void Draw(SDL_Rect camera) {};
private:
	void (*callback)();
};