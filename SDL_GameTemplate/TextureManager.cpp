#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer)
{
   // sent with nullptr
	if (src.w != 0 && src.h != 0)
		SDL_RenderCopy(renderer, tex, &src, &dest);
	else
		SDL_RenderCopy(renderer, tex, nullptr, &dest);

}
