#include "LevelMap.h"

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	mMap = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] mMap[i];
	}
	delete[] mMap;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}

	return 0;
}

/*void LevelMap::Render(float x, float y, SDL_Renderer* renderer)
{
	Vector2D tempPosition(x * 32, y * 32);
	brickTexture->Render(tempPosition, SDL_FLIP_NONE);
}*/