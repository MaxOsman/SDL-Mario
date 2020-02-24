#pragma once
#include "LevelMap.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* levelMap);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; }
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};