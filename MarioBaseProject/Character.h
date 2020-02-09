#pragma once

#define MARIO_GRAVITY_A 1.0f
#define MARIO_WALK_A 0.1f
#define MARIO_RUN_A 0.22f
#define MARIO_GROUND_FRICTION_A 0.15f
#define MARIO_GROUND_CAP 120.0f
#define MARIO_START_VELOCITY_WALK 12.0f
#define MARIO_GROUND_CAP_RUN 220.0f
#define MARIO_START_VELOCITY_RUN 20.0f
#define MARIO_JUMP_SPEED 350.0f
#define MARIO_JUMP_TIME 0.1f

#include "SDL.h"
#include <iostream>
#include "Commons.h"

using namespace std;
class Texture2D;

class Character
{
private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	Vector2D mVelocity;
	Vector2D mAccel;
	bool mIsGrounded;
	bool mIsRunning;
	bool mHoldingJump;
	bool mIsJumping;
	float mJumpTime;
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
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