#include <SDL.h>
#include <SDL_ttf.h>
//#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include <iostream>
#include "GameScreenManager.h"
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
TTF_Font* font;

bool InitSDL();
void CloseSDL();
bool Update();

void Render();
int angle = 0;

int main(int argc, char* args[])
{
	InitSDL();
	TTF_Init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Music Load Error!" << endl;
	} 
	font = TTF_OpenFont("arial.ttf", 20);
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL2, font);
	gOldTime = SDL_GetTicks();
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Success
		gWindow = SDL_CreateWindow("SDL Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		return true;
	}
}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	delete gameScreenManager;
	gameScreenManager = NULL;
	gRenderer = NULL;
	gWindow = NULL;
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);
	cout << SDL_GetError();

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	gameScreenManager->Render();
	SDL_RenderPresent(gRenderer);
}