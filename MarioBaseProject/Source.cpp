#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include <iostream>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//SDL_Texture* gTexture = NULL;
Texture2D* gTexture = NULL;

using namespace std;

bool InitSDL();
void CloseSDL();
bool Update();

void Render();
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();
int angle = 0;

int main(int argc, char* args[])
{
	InitSDL();
	bool quit = false;

	while (!quit)
	{
		Render();
		quit = Update();
	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not inittialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Success
		gWindow = SDL_CreateWindow("Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		/*if (gRenderer != NULL)
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
			else
			{
				cout << "Renderer could not initialise. Error: " << SDL_GetError();
				return false;
			}
		}*/

		gTexture = new Texture2D(gRenderer);
		if (!gTexture->LoadFromFile("Images/test.bmp"))
			return false;
		return true;
	}
}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	delete gTexture;
	gTexture = NULL;
	//FreeTexture();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	gWindow = NULL;
	//IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	cout << SDL_GetError();

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			angle-=6;
			break;
		case SDLK_RIGHT:
			angle+=6;
			break;
		}
		break;
	}

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	gTexture->Render(Vector2D(), SDL_FLIP_NONE);
	SDL_RenderPresent(gRenderer);
}

/*SDL_Texture* LoadTextureFromFile(string path)
{
	FreeTexture();
	SDL_Texture* pTexture = NULL;
	SDL_Surface* pSurface = SDL_LoadBMP(path.c_str());
	pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
	SDL_FreeSurface(pSurface);
	return pTexture;
}

void FreeTexture()
{
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
}*/