#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario) : Character(renderer, imagePath, startPosition, map, isArcadeMario)
{
	mHoldingJump = false;
	mHoldingJumpPreviousFrame = false;
	mIsJumping = false;
	mIsRunning = false;
	mJumpTime = MARIO_JUMP_TIME;
	mSingleSpriteWidth = mTexture->GetWidth() / 7;
	mSingleSpriteHeight = mTexture->GetHeight();
	leftOfTilesheet = 0;
}

CharacterMario::~CharacterMario()
{
	
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	GetInput(e);
	MovementCheck();
	JumpCheck(deltaTime);
	AddFriction();
	SpeedCap(deltaTime);
	GroundCheck();

	mWalkAnimationTime -= deltaTime;
	if (!mIsGrounded)
	{
		leftOfTilesheet = 160;
	}
	else if (!mMovingLeft && !mMovingRight)
	{
		leftOfTilesheet = 0;
	}
	else if((mMovingLeft && mVelocity.x < 0) || (mMovingRight && mVelocity.x > 0))
	{
		if (mWalkAnimationTime <= 0 && leftOfTilesheet < 3 * mSingleSpriteWidth)
		{
			leftOfTilesheet += mSingleSpriteWidth;
			if(!mIsRunning)
				mWalkAnimationTime = MARIO_WALK_TIME;
			else
				mWalkAnimationTime = MARIO_RUN_TIME;
		}
		else if (mWalkAnimationTime <= 0 && leftOfTilesheet >= 3 * mSingleSpriteWidth)
		{
			leftOfTilesheet = mSingleSpriteWidth;
			if (!mIsRunning)
				mWalkAnimationTime = MARIO_WALK_TIME;
			else
				mWalkAnimationTime = MARIO_RUN_TIME;
		}
	}
	else if ((mMovingLeft && mVelocity.x > 0) || (mMovingRight && mVelocity.x < 0))
	{
		leftOfTilesheet = 128;
	}
	
}

/*void CharacterMario::Render()
{
	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
}*/

void CharacterMario::Render()
{
	SDL_Rect portionOfSpriteSheet = { leftOfTilesheet, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	else
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);

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

void CharacterMario::SpeedCap(float deltaTime)
{
	if (mVelocity.x > MARIO_GROUND_CAP && !mIsRunning)
		mVelocity.x = MARIO_GROUND_CAP;
	else if (mVelocity.x < -MARIO_GROUND_CAP && !mIsRunning)
		mVelocity.x = -MARIO_GROUND_CAP;

	if (mVelocity.x > MARIO_GROUND_CAP_RUN && mIsRunning)
		mVelocity.x = MARIO_GROUND_CAP_RUN;
	else if (mVelocity.x < -MARIO_GROUND_CAP_RUN && mIsRunning)
		mVelocity.x = -MARIO_GROUND_CAP_RUN;
}

void CharacterMario::GroundCheck()
{
	centralXPosition = (int)(mPosition.x + (mSingleSpriteWidth * 0.5f)) / TILE_WIDTH;
	leftXPosition = (int)mPosition.x / TILE_WIDTH;
	rightXPosition = (int)(mPosition.x + mSingleSpriteWidth) / TILE_WIDTH;
	footPosition = (int)(mPosition.y + mSingleSpriteHeight) / TILE_WIDTH;
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
	//cout << mIsGrounded << "  " << mHoldingJumpPreviousFrame << " " << mHoldingJump << "  " << mIsJumping << "  " << mJumpTime << endl;
	if ((mIsGrounded && !mHoldingJumpPreviousFrame && mHoldingJump && !mIsJumping && mJumpTime > 0) ||
		(!mIsGrounded && mHoldingJump && mIsJumping && mJumpTime > 0))
	{
		if (mVelocity.y == 0)
			mVelocity.y = 1 * deltaTime;

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
	mJumpTime = 0;
	mIsJumping = false;
}

void CharacterMario::KoopaBounce(float deltaTime)
{
	if(!mHoldingJump)
		mVelocity.y = -MARIO_BOUNCE_SPEED;
	else
		mVelocity.y = -MARIO_BOUNCE_SPEED * 4;
	mJumpTime = 0;
	mIsJumping = false;
}