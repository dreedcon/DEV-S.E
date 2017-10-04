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
	idle.speed = 0.01f;

	walk_right.PushBack({ 0,  30, 30, 30 });
	walk_right.PushBack({ 30, 30, 30, 30 });
	walk_right.PushBack({ 60, 30, 30, 30 });
	walk_right.PushBack({ 90, 30, 30, 30 });
	walk_right.speed = 0.01f;

	jump_right.PushBack({ 0, 60, 30, 30 });
	jump_right.PushBack({ 30, 60, 30, 30 });
	jump_right.PushBack({ 60, 60, 30, 30 });
	jump_right.speed = 0.01f;

	run_right.PushBack({ 0,  90, 30, 30 });
	run_right.PushBack({ 30, 90, 30, 30 });
	run_right.PushBack({ 60, 90, 30, 30 });
	run_right.PushBack({ 90, 90, 30, 30 });
	run_right.speed = 0.01f;
	// ------------------
	fly_right.PushBack({ 0, 120, 30, 30 });
	fly_right.PushBack({ 30, 120, 30, 30 });
	fly_right.PushBack({ 60, 120, 30, 30 });
	fly_right.speed = 0.01f;

	walk_left.PushBack({ 0,  150, 30, 30 });
	walk_left.PushBack({ 30, 150, 30, 30 });
	walk_left.PushBack({ 60, 150, 30, 30 });
	walk_left.PushBack({ 90, 150, 30, 30 });
	walk_left.speed = 0.01f;

	jump_left.PushBack({ 0, 180, 30, 30 });
	jump_left.PushBack({ 30, 180, 30, 30 });
	jump_left.PushBack({ 60, 180, 30, 30 });
	jump_left.speed = 0.01f;

	run_left.PushBack({ 0,  210, 30, 30 });
	run_left.PushBack({ 30, 210, 30, 30 });
	run_left.PushBack({ 60, 210, 30, 30 });
	run_left.PushBack({ 90, 210, 30, 30 });
	run_left.speed = 0.01f;

	fly_left.PushBack({ 0, 240, 30, 30 });
	fly_left.PushBack({ 30, 240, 30, 30 });
	fly_left.PushBack({ 60, 240, 30, 30 });
	fly_left.speed = 0.01f;





}

Player::~Player()
{
}

bool Player::Awake(pugi::xml_node& config)
{
	position.create(50, 50);
	velocity.create(0, 0);
	// Sprites
	return true;
}

bool Player::Start()
{
	graphics = App->tex->Load("textures/Kirby.png");
	current_animation = &idle;
	state = IDLE;
	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{
	//Set zero
	//Setzero();

	Input();
	processPos();
	processGravity();
	Draw();
	return true;
}

void Player::Input()
{
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		direction = LEFT;
		if (App->map->MovementCost(position.x, position.y, 30, 30, direction))
		{
			position.x -= 0.2f;
		}
		if (!isFly)
			state = W_LEFT;
		else if (state == FLY_RIGHT)
			state = FLY_LEFT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		direction = NON;

		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		direction = LEFT;
		if (App->map->MovementCost(position.x, position.y, 30, 30, direction))
		{
			position.x -= 0.5f;
		}
		if (!isFly)state = RUN_LEFT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_UP)
	{
		direction = NON;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		direction = RIGHT;
		if (App->map->MovementCost(position.x, position.y - 1, 30, 30, direction))
		{
			position.x += 0.2f;
		}
		if (!isFly)state = W_RIGHT;
		else if (state == FLY_LEFT)
			state = FLY_RIGHT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		direction = NON;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		direction = RIGHT;
		if (App->map->MovementCost(position.x, position.y, 30, 30, direction))
		{
			position.x += 0.5f;
		}
		if (!isFly)state = RUN_RIGHT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_E) == KEY_UP)
	{
		direction = NON;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (isFly == false)
		{
			//JUMP!!!!
			if (state == W_LEFT || state == RUN_LEFT)
			{
				state = JUMP_LEFT;
				velocity.y -= 1;
				isFly = true;
			}
			if (state == W_RIGHT || state == RUN_RIGHT || state == IDLE)
			{
				velocity.y -= 1;
				state = JUMP_RIGHT;
				isFly = true;
			}
		}
		else
		{
			if (state == FLY_LEFT || state == FLY_RIGHT)
			{
				isFly = false;
				state = IDLE;
			}
			else
			{
				if (direction == LEFT)
				{
					state = FLY_LEFT;
				}
				if (direction == RIGHT || direction == NON)
				{
					state = FLY_RIGHT;
				}
			}
		}

	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		direction = NON;
	}
}

void Player::Setzero()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Player::processPos()
{
	position.x = position.x + velocity.x;   // Change position based on 
	position.y = position.y + velocity.y;   // current velocity components.
}

void Player::processGravity()
{
	if (App->map->MovementCost(position.x, position.y, 30, 30, DOWN) && state != FLY_LEFT && state != FLY_RIGHT)
	{
		velocity.y += Gravity / 4;
	}
	else if (isFly == false)
	{
		velocity.y = 0;
	}
	else
	{
		if (App->map->MovementCost(position.x, position.y, 30, 30, DOWN) == false)
		{
			isFly = false;
			velocity.y = 0;
			state = IDLE;
		}
		else
		{
			LOG("LOL");
			velocity.y = 0.06;
		}
	}



}

void Player::Draw()
{
	switch (state)
	{
	case IDLE:
	{
		current_animation = &idle;
		break;
	}
	case W_LEFT:
	{
		current_animation = &walk_left;
		break;
	}
	case W_RIGHT:
	{
		current_animation = &walk_right;
		break;
	}
	case RUN_LEFT:
	{
		current_animation = &run_left;
		break;
	}
	case RUN_RIGHT:
	{
		current_animation = &run_right;
		break;
	}
	case JUMP_LEFT:
	{
		current_animation = &jump_left;
		break;
	}
	case JUMP_RIGHT:
	{
		current_animation = &jump_right;
		break;
	}
	case FLY_LEFT:
	{
		current_animation = &fly_left;
		break;
	}
	case FLY_RIGHT:
	{
		current_animation = &fly_right;
		break;
	}
	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x, position.y, &r);
}

bool Player::PostUpdate()
{
	return true;
}

bool Player::CleanUp()
{
	return true;
}
