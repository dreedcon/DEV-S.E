#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"

#define Gravity 0.02

struct SDL_Texture;

enum State
{
	IDLE,
	W_LEFT,
	W_RIGHT,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	FLY_LEFT,
	FLY_RIGHT
};

enum Direction
{
	NON,
	UP,
	LEFT,
	DOWN,
	RIGHT
};

class Player : public j1Module
{
public:

	Player();

	// Destructor
	virtual ~Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void Input();

	void Setzero();

	void processPos();

	void processGravity();

	void ReturnToZero();

	void Draw();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	fPoint position;
	fPoint velocity;
	bool isFly = false;
	bool returntoZero = false;
	Direction goZero = NON;

	//TODO SERGIO 1
	//Create 3 variables (2 iPoint / 1 enum LVL)



public:
	State state;
	Direction direction;

	//Animations
	Animation* current_animation;
	Animation idle;
	Animation walk_left;
	Animation walk_right;
	Animation run_left;
	Animation run_right;
	Animation jump_left;
	Animation jump_right;
	Animation fly_left;
	Animation fly_right;


};

#endif // __PLAYER_H__