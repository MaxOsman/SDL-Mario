#pragma once
#include "Character.h"

using namespace std;
//class Texture2D;

class CharacterMario : public Character
{
private:
	bool mIsRunning;
	bool mHoldingJump;
	bool mHoldingJumpPreviousFrame;
	bool mIsJumping;
	float mJumpTime;

public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, SoundEffect* sounds);
	~CharacterMario();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SpeedCap(float deltaTime);
	void GroundCheck();
	void MovementCheck();
	void AddFriction();
	void GetInput(SDL_Event e);
	void JumpCheck(float deltaTime);
	void CancelJump();
	void SetPosition(Vector2D newPosition);
	void KoopaBounce(float deltaTime);
	void UpdateAnimation();
	Vector2D GetVelocity() { return mVelocity; }
	Texture2D* GetTexture() { return mTexture; }
};