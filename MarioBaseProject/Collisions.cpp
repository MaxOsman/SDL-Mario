#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if (!mInstance)
		mInstance = new Collisions;

	return mInstance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.w / 2) > rect2.x&&
		rect1.x + (rect1.w / 2) < rect2.x + rect2.w &&
		rect1.y + (rect1.h / 2) > rect2.y&&
		rect1.y + (rect1.h / 2) < rect2.y + rect2.h)
	{
		return true;
	}

	return false;
}