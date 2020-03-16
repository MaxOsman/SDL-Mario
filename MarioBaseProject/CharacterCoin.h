#pragma once
#include "Character.h"

class CharacterCoin : public Character
{
private:

public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING direction);
	~CharacterCoin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ScreenSideCheck();
	void GroundCheck();
};