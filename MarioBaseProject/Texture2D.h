#pragma once
#define _TEXTURE2D_H

#include "SDL.h"
#include <iostream>
#include "Commons.h"
using namespace std;

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	void Free();
	void Render(Vector2D newPosition, SDL_RendererFlip flip);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};