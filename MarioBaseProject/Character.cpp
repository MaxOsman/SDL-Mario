#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario)
{
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture.";
	}
	mIsGrounded = false;
	mCurrentLevelMap = map;
}

Character::~Character()
{
	mRenderer = NULL;
	delete mTexture;
}

void Character::Render()
{
	
}

void Character::Update(float deltaTime, SDL_Event e)
{
	GroundCheck();
	AddGravity();
	AddVelocity(deltaTime);
	ScreenSideCheck();
}

void Character::AddVelocity(float deltaTime)
{
	mVelocity.x += mAccel.x;
	mVelocity.y += mAccel.y;

	mPosition.x += mVelocity.x * deltaTime;
	mPosition.y += mVelocity.y * deltaTime;
}

void Character::AddGravity()
{
	if (!mIsGrounded)
		mAccel.y = MARIO_GRAVITY_A;
	else
	{
		mAccel.y = 0;
		mVelocity.y = 0;
	}
}

void Character::GroundCheck()
{
	
}

void Character::ScreenSideCheck()
{
	if (mPosition.x < -MARIO_WIDTH / 2)
	{
		mPosition.x = 512 - MARIO_WIDTH / 2;
	}
	if (mPosition.x > 512 - MARIO_WIDTH / 2)
	{
		mPosition.x = -MARIO_WIDTH / 2;
	}
}