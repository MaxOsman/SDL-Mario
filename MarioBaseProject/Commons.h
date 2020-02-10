#pragma once

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

struct Vector2D
{
	float x;
	float y;
	Vector2D(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	Vector2D()
	{
		x = 0;
		y = 0;
	}
};

struct Rect2D
{
	float x;
	float y;
	float w;
	float h;
	Rect2D(float xx, float yy, float ww, float hh)
	{
		x = xx;
		y = yy;
		w = ww;
		h = hh;
	}
	Rect2D()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
};
