#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{
	sounds.clear();
}

void SoundEffect::AddSound(const char* path, SOUNDS index)
{
	IndexedSound tempSound = {Mix_LoadWAV(path), index};
	sounds.push_back(tempSound);
}

void SoundEffect::Play(SOUNDS index)
{
	for (int i = 0; i < sounds.size(); ++i)
	{
		if ((int)index == sounds[i].index)
		{
			Mix_PlayChannelTimed(-1, sounds[i].chunk, 0, -1);
		}	
	}
}

void SoundEffect::ClearAll()
{
	sounds.clear();
}