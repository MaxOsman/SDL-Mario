#pragma once
#include "SDL.h"
#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();
	Collisions();

	bool Circle(Vector2D center1, Vector2D center2, float radius);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	
};