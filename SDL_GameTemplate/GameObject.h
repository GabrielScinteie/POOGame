#pragma once
#include "SDL_image.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer);
	virtual ~GameObject();

	void virtual Update();
	void virtual Render() = 0;

protected:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
};