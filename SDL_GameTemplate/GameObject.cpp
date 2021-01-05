#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>


GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer)
{
   this -> renderer = renderer;
   texture = TextureManager::LoadTexture(textureSheet, renderer);
   srcRect.h = 0;
   srcRect.w = 0;
   srcRect.x = 0;
   srcRect.y = 0;



   destRect.x = 64;
   destRect.y = 64;
   destRect.w = 32;
   destRect.h = 32;
}

GameObject::~GameObject() = default;

void GameObject::Update() {

}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}