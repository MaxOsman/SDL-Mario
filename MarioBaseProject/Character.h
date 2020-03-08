#pragma once
#include "LevelMap.h"

class Character
{
protected:
	float centralXPosition;
	float leftXPosition;
	float rightXPosition;
	float footPosition;
	float headPosition;
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	Vector2D mVelocity;
	Vector2D mAccel;
	bool mIsGrounded;

	float mWalkAnimationTime;
	int leftOfTilesheet;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mCurrentLevelMap;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void AddVelocity(float deltaTime);
	void AddGravity();
	virtual void GroundCheck();
	virtual void ScreenSideCheck();

	bool isAlive;

	Vector2D GetPosition() { return mPosition; }
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); }
};