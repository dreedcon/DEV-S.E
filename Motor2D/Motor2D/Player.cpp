#include "Player.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Scene.h"

Player::Player()
{

	idle.PushBack({ 0,  0, 30, 30 });
	idle.PushBack({ 30, 0, 30, 30 });
	idle.PushBack({ 60, 0, 30, 30 });
	idle.PushBack({ 90, 0, 30, 30 });
	idle.speed = 0.3f;

	walk_right.PushBack({ 0,  30, 30, 30 });
	walk_right.PushBack({ 30, 30, 30, 30 });
	walk_right.PushBack({ 60, 30, 30, 30 });
	walk_right.PushBack({ 90, 30, 30, 30 });
	walk_right.speed = 0.3f;

	jump_right.PushBack({ 0, 60, 30, 30 });
	jump_right.PushBack({ 30, 60, 30, 30 });
	jump_right.PushBack({ 60, 60, 30, 30 });
	jump_right.speed = 0.3f;

	run_right.PushBack({ 0,  90, 30, 30 });
	run_right.PushBack({ 30, 90, 30, 30 });
	run_right.PushBack({ 60, 90, 30, 30 });
	run_right.PushBack({ 90, 90, 30, 30 });
	run_right.speed = 0.3f;
	// ------------------
	fly_right.PushBack({ 0, 120, 30, 30 });
	fly_right.PushBack({ 30, 120, 30, 30 });
	fly_right.PushBack({ 60, 120, 30, 30 });
	fly_right.speed = 0.3f;

	walk_left.PushBack({ 0,  150, 30, 30 });
	walk_left.PushBack({ 30, 150, 30, 30 });
	walk_left.PushBack({ 60, 150, 30, 30 });
	walk_left.PushBack({ 90, 150, 30, 30 });
	walk_left.speed = 0.3f;

	jump_left.PushBack({ 0, 180, 30, 30 });
	jump_left.PushBack({ 30, 180, 30, 30 });
	jump_left.PushBack({ 60, 180, 30, 30 });
	jump_left.speed = 0.3f;

	run_left.PushBack({ 0,  210, 30, 30 });
	run_left.PushBack({ 30, 210, 30, 30 });
	run_left.PushBack({ 60, 210, 30, 30 });
	run_left.PushBack({ 90, 210, 30, 30 });
	run_left.speed = 0.3f;

	fly_left.PushBack({ 0, 240, 30, 30 });
	fly_left.PushBack({ 30, 240, 30, 30 });
	fly_left.PushBack({ 60, 240, 30, 30 });
	fly_left.speed = 0.3f;





}

Player::~Player()
{
}

bool Player::Awake(pugi::xml_node& config)
{
	position.create(50, 50);
	// Sprites
	return true;
}

bool Player::Start()
{
	img = App->tex->Load("textures/Player_test.png");

	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		position.y += 1;
	}

	App->render->Blit(img, position.x, position.y);

	return true;
}

bool Player::PostUpdate()
{
	return true;
}

bool Player::CleanUp()
{
	return true;
}
