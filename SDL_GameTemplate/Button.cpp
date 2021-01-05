#include "Button.h"

Button::Button(const char* textureSheet, void (*callback) (), SDL_Renderer* renderer, SDL_Rect _srcrec, SDL_Rect _destrec) : GameObject(textureSheet, renderer)
{
	srcRect = _srcrec;
	destRect = _destrec;
	this->callback = callback;
};

void Button::Render()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}

void Button::pressed()
{
	(*callback)();
}

bool Button::inside(int x, int y)
{
	if (x > destRect.x && x < destRect.x + destRect.w && y > destRect.y && y < destRect.y + destRect.h)
		return 1;
	return 0;
}