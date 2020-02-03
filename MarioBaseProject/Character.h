#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"

using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
};