#pragma once
#include "Commons.h"
#include <SDL_mixer.h>
#include <vector>
#include <iostream>
using namespace std;

class SoundEffect
{
private:
	vector<IndexedSound> sounds;
public:
	SoundEffect();
	~SoundEffect();

	void AddSound(const char* path, SOUNDS index);
	void Play(SOUNDS index);
	void ClearAll();
};