#include "LevelMap.h"

LevelMap::LevelMap(char map[MAP_HEIGHT][MAP_WIDTH])
{
	mMap = new char* [MAP_HEIGHT];
	for (unsigned char i = 0; i < MAP_HEIGHT; ++i)
	{
		mMap[i] = new char[MAP_WIDTH];
	}
}

LevelMap::LevelMap(char map[MAP_HEIGHT][MAP_WIDTH], string path2, string path3, string path4, SDL_Renderer* renderer)
{
	mMap = new char* [MAP_HEIGHT];
	for (unsigned char i = 0; i < MAP_HEIGHT; ++i)
	{
		mMap[i] = new char[MAP_WIDTH];
	}
	m2Texture = new Texture2D(renderer);
	if (!m2Texture->LoadFromFile(path2))
	{
		cout << "Failed to load texture 2.";
	}
	m3Texture = new Texture2D(renderer);
	if (!m3Texture->LoadFromFile(path3))
	{
		cout << "Failed to load texture 3.";
	}
	m3SpriteSize.x = m3Texture->GetWidth() / 3;
	m3SpriteSize.y = m3Texture->GetHeight();
	m4Texture = new Texture2D(renderer);
	if (!m4Texture->LoadFromFile(path4))
	{
		cout << "Failed to load texture 4.";
	}
	leftOfTilesheet = 0;
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; ++i)
	{
		delete[] mMap[i];
	}
	delete[] mMap;
	delete m2Texture;
	delete m3Texture;
	delete m4Texture;
}

char LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned char newValue)
{
	mMap[row][column] = newValue;
}

//File loading from the S2D platformer
void LevelMap::LoadMapFromFile(int levelName)
{
	int width;
	vector<string>* lines = new vector<string>();
	fstream stream;
	stringstream ss;
	ss << "Maps/" << levelName << ".txt";
	stream.open(ss.str(), fstream::in);

	char* line = new char[256];
	stream.getline(line, 256);
	string* sline = new string(line);
	width = sline->size();

	while (!stream.eof())
	{
		lines->push_back(*sline);
		if (sline->size() != width)
			cout << "Level load failed!" << endl;
		stream.getline(line, 256);
		delete sline;
		sline = new string(line);
	}
	delete[] line;
	delete sline;

	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			char tile = lines->at(y)[x];
			mMap[y][x] = tile;
		}
	}

	delete lines;
}

void LevelMap::Render()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; ++j)
		{
			SDL_Rect destRect = { j * 32, i * 32, m3SpriteSize.x, m3SpriteSize.y };
			SDL_Rect portionOfSpriteSheet = { leftOfTilesheet, 0, m3SpriteSize.x, m3SpriteSize.y };

			if (GetTileAt(i, j) == '2')
				m2Texture->Render(Vector2D(j * 32, i * 32), SDL_FLIP_NONE);
			if (GetTileAt(i, j) == '3')
				m3Texture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
				//m3Texture->Render(Vector2D(j * 32, i * 32), SDL_FLIP_NONE);
			if (GetTileAt(i, j) == '4')
				m4Texture->Render(Vector2D(j * 32, i * 32), SDL_FLIP_NONE);
		}
	}
}

void LevelMap::Update(float deltaTime)
{
	mBlockAnimationTime -= deltaTime;
	if (mBlockAnimationTime <= 0 && leftOfTilesheet < 2 * m3SpriteSize.x)
	{
		leftOfTilesheet += m3SpriteSize.x;
		mBlockAnimationTime = COINBLOCK_ANIMATION_TIME;
	}
	else if (mBlockAnimationTime <= 0 && leftOfTilesheet >= 2 * m3SpriteSize.x)
	{
		leftOfTilesheet = 0;
		mBlockAnimationTime = COINBLOCK_ANIMATION_TIME;
	}
}