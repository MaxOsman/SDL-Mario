#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition)
{
	mFacingDirection = FACING_RIGHT;
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture.";
	}
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
	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	AddVelocity(deltaTime);
	AddAcceleration(deltaTime);

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
		}
		break;
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= marioSpeed * deltaTime;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += marioSpeed * deltaTime;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += marioGravity * deltaTime;
}