#pragma once
#include "Constants.h"
#include "Texture2D.h"

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();
	//void Render(float x, float y, SDL_Renderer* renderer);
	int GetTileAt(unsigned int h, unsigned int w);

private:
	int** mMap;
	//SDL_Renderer* mRenderer;
};