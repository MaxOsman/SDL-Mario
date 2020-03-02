#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario) : Character(renderer, imagePath, startPosition, map, isArcadeMario)
{
	mHoldingJump = false;
	mHoldingJumpPreviousFrame = false;
	mIsJumping = false;
	mIsRunning = false;
	mJumpTime = MARIO_JUMP_TIME;
}

CharacterMario::~CharacterMario()
{
	
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	GetInput(e);

	//GroundCheck();
	MovementCheck();
	//AddGravity();
	JumpCheck(deltaTime);

	AddFriction();

	SpeedCap();

	//AddVelocity(deltaTime);
	//ScreenSideCheck();
}

void CharacterMario::Render()
{
	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
}

void CharacterMario::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

void CharacterMario::MovementCheck()
{
	if (mMovingLeft && !(mVelocity.x > -0.12 && mVelocity.x < 0.05))
	{
		mFacingDirection = FACING_LEFT;
		if(!mIsRunning)
			mAccel.x = -MARIO_WALK_A;
		else
			mAccel.x = -MARIO_RUN_A;
	}
	else if (mMovingLeft && (mVelocity.x > -0.12 && mVelocity.x < 0.05))
	{
		mFacingDirection = FACING_LEFT;
		if (!mIsRunning)
		{
			mAccel.x = -MARIO_WALK_A;
			mVelocity.x = -MARIO_START_VELOCITY_WALK;
		}	
		else
		{
			mAccel.x = -MARIO_RUN_A;
			mVelocity.x = -MARIO_START_VELOCITY_RUN;
		}			
	}

	if (mMovingRight && !(mVelocity.x > -0.12 && mVelocity.x < 0.05))
	{
		mFacingDirection = FACING_RIGHT;
		if (!mIsRunning)
			mAccel.x = MARIO_WALK_A;
		else
			mAccel.x = MARIO_RUN_A;
	}
	else if (mMovingRight && (mVelocity.x > -0.12 && mVelocity.x < 0.05))
	{
		mFacingDirection = FACING_RIGHT;
		if (!mIsRunning)
		{
			mAccel.x = MARIO_WALK_A;
			mVelocity.x = MARIO_START_VELOCITY_WALK;
		}
		else
		{
			mAccel.x = MARIO_RUN_A;
			mVelocity.x = MARIO_START_VELOCITY_RUN;
		}
	}
}

void CharacterMario::SpeedCap()
{
	if (mVelocity.x > MARIO_GROUND_CAP && !mIsRunning)
		mVelocity.x -= 0.2;
	else if (mVelocity.x < -MARIO_GROUND_CAP && !mIsRunning)
		mVelocity.x += 0.2;

	if (mVelocity.x > MARIO_GROUND_CAP_RUN && mIsRunning)
		mVelocity.x = MARIO_GROUND_CAP_RUN;
	else if (mVelocity.x < -MARIO_GROUND_CAP_RUN && mIsRunning)
		mVelocity.x = -MARIO_GROUND_CAP_RUN;
}

void CharacterMario::GroundCheck()
{
	centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	leftXPosition = (int)mPosition.x / TILE_WIDTH;
	rightXPosition = (int)(mPosition.x + mTexture->GetWidth()-1) / TILE_WIDTH;
	footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_WIDTH;
	headPosition = (int)mPosition.y / TILE_WIDTH;
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1 && mIsJumping == false)
	{
		mPosition.y = (footPosition - 1) * TILE_WIDTH;
		mIsGrounded = true;
		mJumpTime = MARIO_JUMP_TIME; 
		mAccel.y = 0;
		mVelocity.y = 0;
	}
	else
	{
		mIsGrounded = false;
	}

	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition) == 1)
	{
		mPosition.y = (headPosition + 1) * TILE_WIDTH;
		CancelJump();
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, leftXPosition) == 1 && mCurrentLevelMap->GetTileAt(footPosition - 1, leftXPosition) == 1)
	{
		mPosition.x = (leftXPosition + 1) * TILE_WIDTH;
		mVelocity.x = 0;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, rightXPosition) == 1 && mCurrentLevelMap->GetTileAt(footPosition - 1, rightXPosition) == 1)
	{
		mPosition.x = (rightXPosition - 1) * TILE_WIDTH;
		mVelocity.x = 0;
	}
}

void CharacterMario::JumpCheck(float deltaTime)
{
	cout << mIsGrounded << "  " << !mHoldingJumpPreviousFrame << " " << mHoldingJump << "  " << mIsJumping << "  " << mJumpTime << endl;

	if ((mIsGrounded && !mHoldingJumpPreviousFrame && mHoldingJump && !mIsJumping && mJumpTime > 0) ||
		(!mIsGrounded && mHoldingJump && mIsJumping && mJumpTime > 0))
	{
		if (mVelocity.y == 0)
			mVelocity.y = 1;

		if(mVelocity.x >= 0)
			mVelocity.y = -(MARIO_JUMP_SPEED + mVelocity.x*0.3);
		else
			mVelocity.y = -(MARIO_JUMP_SPEED - mVelocity.x*0.3);

		mJumpTime -= deltaTime;
		mIsJumping = true;
		mIsGrounded = false;
		if (mJumpTime <= 0)
		{
			mIsJumping = false;
		}		
	}
	if (!mIsGrounded && !mHoldingJump)
	{
		mIsJumping = false;
		mJumpTime = MARIO_JUMP_TIME;
	}
}

void CharacterMario::AddFriction()
{
	//if (mIsGrounded)
	//{
		if (!mMovingLeft && !mMovingRight && mVelocity.x < -0.01)
		{
			mAccel.x = MARIO_GROUND_FRICTION_A;
		}
		else if (!mMovingLeft && mMovingRight && mVelocity.x < -0.01)
		{
			mAccel.x = MARIO_GROUND_FRICTION_A * 2;
		}
		else if (!mMovingLeft && !mMovingRight && mVelocity.x > 0.01)
		{
			mAccel.x = -MARIO_GROUND_FRICTION_A;
		}
		else if (mMovingLeft && !mMovingRight && mVelocity.x > 0.01)
		{
			mAccel.x = -MARIO_GROUND_FRICTION_A * 2;
		}

		if (mVelocity.x > -0.01 && mVelocity.x < 0.01)
		{
			mVelocity.x = 0;
			mAccel.x = 0;
		}
	//}
}

void CharacterMario::GetInput(SDL_Event e)
{
	mHoldingJumpPreviousFrame = mHoldingJump;
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			break;
		case SDLK_x:
			mHoldingJump = true;
			break;
		case SDLK_z:
			mIsRunning = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		case SDLK_x:
			mHoldingJump = false;
			break;
		case SDLK_z:
			mIsRunning = false;
			break;
		}
		break;
	}
}

void CharacterMario::CancelJump()
{
	mVelocity.y = 0;
	mAccel.y = MARIO_GRAVITY_A;
	mJumpTime = 0;
	mIsJumping = false;
}