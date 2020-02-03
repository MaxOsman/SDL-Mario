#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;
	mWidth;
	mHeight;
}
Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	Free();
	SDL_Surface* pSurface = SDL_LoadBMP(path.c_str());
	SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
	if (mTexture != NULL)
	{
		mWidth = pSurface->w;
		mHeight = pSurface->h;
	}
	mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
	SDL_FreeSurface(pSurface);
	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Texture2D::Render(Vector2D newPosition, int angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0x45, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);
	SDL_Rect renderLocation = {0, 0, mWidth, mHeight};
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, 0, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(mRenderer);
}