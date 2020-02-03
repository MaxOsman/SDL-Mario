#pragma once

#define MARIO_GRAVITY_A 50.0f
#define MARIO_WALK_A 25.0f

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
	float marioVx;
	float marioVy;
	float marioAx;
	float marioAy;
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	void AddVelocity(float deltaTime);
	void AddAcceleration(float deltaTime);
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
};