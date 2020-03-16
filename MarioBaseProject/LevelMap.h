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
	LevelMap(char map[MAP_HEIGHT][MAP_WIDTH], string path2, string path3, string path4, SDL_Renderer* renderer);
	~LevelMap();
	void Render();
	char GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue);
	void LoadMapFromFile(int levelName);

private:
	char** mMap;
	Texture2D* m2Texture;
	Texture2D* m3Texture;
	Texture2D* m4Texture;
};