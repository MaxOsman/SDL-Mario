#include "Collisions.h"

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.y + rect1.h < rect2.y)
		return false;
	if (rect1.y > rect2.y + rect2.h)
		return false;
	if (rect1.x + rect1.w < rect2.x)
		return false;
	if (rect1.x > rect2.x + rect2.w)
		return false;

	return true;
}

bool Collisions::Circle(Vector2D center1, Vector2D center2, float radius)
{
	float distance = sqrt((center1.x - center2.x) * (center1.x - center2.x) + (center1.y - center2.y) * (center1.y - center2.y));
	if (distance <= radius)
		return true;

	return false;
}