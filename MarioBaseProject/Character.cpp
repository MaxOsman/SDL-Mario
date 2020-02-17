#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mRenderer = renderer;
	mHoldingJump = false;
	mHoldingJumpPreviousFrame = false;
	mIsJumping = false;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture.";
	}
	mIsGrounded = false;
	mIsRunning = false;
	mJumpTime = MARIO_JUMP_TIME;
	mCurrentLevelMap = map;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	if(mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	GetInput(e);

	GroundCheck();
	MovementCheck();
	AddGravity();
	JumpCheck(deltaTime);

	AddFriction();

	SpeedCap();

	AddVelocity(deltaTime);
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::AddVelocity(float deltaTime)
{
	mVelocity.x += mAccel.x;
	mVelocity.y += mAccel.y;

	mPosition.x += mVelocity.x * deltaTime;
	mPosition.y += mVelocity.y * deltaTime;
}

void Character::MovementCheck()
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

void Character::SpeedCap()
{
	//if (mIsGrounded)
	//{
		if (mVelocity.x > MARIO_GROUND_CAP && !mIsRunning)
			mVelocity.x -= 0.2;
		else if (mVelocity.x < -MARIO_GROUND_CAP && !mIsRunning)
			mVelocity.x += 0.2;

		if (mVelocity.x > MARIO_GROUND_CAP_RUN && mIsRunning)
			mVelocity.x = MARIO_GROUND_CAP_RUN;
		else if (mVelocity.x < -MARIO_GROUND_CAP_RUN && mIsRunning)
			mVelocity.x = -MARIO_GROUND_CAP_RUN;
	//}
}

void Character::AddGravity()
{
	if (!mIsGrounded && !mIsJumping)
		mAccel.y = MARIO_GRAVITY_A;
	else
	{
		mAccel.y = 0;
		mVelocity.y = 0;
	}		
}

void Character::GroundCheck()
{
	centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	leftXPosition = (int)mPosition.x / TILE_WIDTH;
	rightXPosition = (int)(mPosition.x + mTexture->GetWidth()) / TILE_WIDTH;
	footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_WIDTH;
	headPosition = (int)mPosition.y / TILE_WIDTH;
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) != 0 && mIsJumping == false)
	{
		mPosition.y = (footPosition - 1) * TILE_WIDTH;
		mIsGrounded = true;
		mJumpTime = MARIO_JUMP_TIME;
	}
	else
		mIsGrounded = false;
	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition) != 0)
	{
		mPosition.y = (headPosition + 1) * TILE_WIDTH;
		mVelocity.y = 0;
		mAccel.y = MARIO_GRAVITY_A;
		mJumpTime = 0;
		mIsJumping = false;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, leftXPosition) != 0)
	{
		mPosition.x = (leftXPosition + 1) * TILE_WIDTH;
		mVelocity.x = 0;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, rightXPosition) != 0)
	{
		mPosition.x = (rightXPosition - 1) * TILE_WIDTH;
		mVelocity.x = 0;
	}
}

void Character::JumpCheck(float deltaTime)
{
	cout << mIsGrounded << "  " << !mHoldingJumpPreviousFrame << " " << mHoldingJump << "  " << mIsJumping << "  " << mJumpTime << endl;

	if ((mIsGrounded && !mHoldingJumpPreviousFrame && mHoldingJump && !mIsJumping && mJumpTime > 0) ||
		(!mIsGrounded && mHoldingJump && mIsJumping && mJumpTime > 0))
	{
		if (mVelocity.y == 0)
			mVelocity.y = 1;

		if(mVelocity.x >= 0)
			mVelocity.y = -(MARIO_JUMP_SPEED + mVelocity.x*0.4);
		else
			mVelocity.y = -(MARIO_JUMP_SPEED - mVelocity.x*0.4);

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

void Character::AddFriction()
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

void Character::GetInput(SDL_Event e)
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