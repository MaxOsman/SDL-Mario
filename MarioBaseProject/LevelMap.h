#pragma once
#include "Constants.h"
#include "Texture2D.h"
#include <fstream>
#include <vector>
#include <sstream>

class LevelMap
{
public:
	LevelMap(char map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();
	//void Render(float x, float y, SDL_Renderer* renderer);
	char GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue);
	void LoadMapFromFile(int levelName);

private:
	char** mMap;
	//SDL_Renderer* mRenderer;
};