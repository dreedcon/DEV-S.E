#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

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

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	SDL_Texture* img = nullptr;
	iPoint position;

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