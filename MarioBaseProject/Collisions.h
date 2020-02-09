#pragma once
#include <vector>
#include "SDL.h"
#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Pixel();
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();
	static Collisions* mInstance;
};