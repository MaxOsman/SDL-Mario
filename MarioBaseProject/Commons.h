#pragma once
#include "SDL_mixer.h"

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_BEAT1,
	SCREEN_NULL,
	SCREEN_BEAT2
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum COLOUR
{
	KOOPA_GREEN = 0,
	KOOPA_RED,
	KOOPA_PURPLE
};

enum SOUNDS
{
	SOUND_JUMP = 0,
	SOUND_BUMP,
	SOUND_STOMP,
	SOUND_POW,
	SOUND_COIN,
	SOUND_DIE
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

struct IndexedSound
{
	Mix_Chunk* chunk;
	SOUNDS index;
};