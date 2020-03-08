#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
private:
	bool mInjured;
	float mInjuredTime;

	void FlipRightWayUp();

	int mType;
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario, FACING direction, COLOUR type);
	~CharacterKoopa();

	void GroundCheck();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void TakeDamage();
	void ScreenSideCheck();
	bool GetInjuredState() { return mInjured; }
};