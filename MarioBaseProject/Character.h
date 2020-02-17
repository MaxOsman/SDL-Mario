#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"

using namespace std;
//class Texture2D;

class Character
{
private:
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
	bool mIsRunning;
	bool mHoldingJump;
	bool mHoldingJumpPreviousFrame;
	bool mIsJumping;
	float mJumpTime;
	LevelMap* mCurrentLevelMap;
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void AddVelocity(float deltaTime);
	void AddGravity();
	void SpeedCap();
	void GroundCheck();
	void MovementCheck();
	void AddFriction();
	void GetInput(SDL_Event e);
	void JumpCheck(float deltaTime);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
	}
};