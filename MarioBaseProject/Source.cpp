#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>

SDL_Window* gWindow = NULL;

using namespace std;

bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[])
{
	InitSDL();
	bool quit = false;

	while (!quit)
	{
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

		return true;
	}
}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
			return true;
		break;
	}

	return false;
}