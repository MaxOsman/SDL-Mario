#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;

	void FlipRightWayUp();
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario, FACING direction);
	~CharacterKoopa();

	void GroundCheck();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void TakeDamage();
	void ScreenSideCheck();
};