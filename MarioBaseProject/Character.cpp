#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition)
{
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
	mTexture->Render(mPosition, 0);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_QUIT:
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mPosition.x--;
			break;
		case SDLK_RIGHT:
			mPosition.x++;
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