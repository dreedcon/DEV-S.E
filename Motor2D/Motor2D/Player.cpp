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

	idle.PushBack({ 3,  5, 24, 21 });
	idle.PushBack({ 33, 5, 24, 21 });
	idle.PushBack({ 62, 5, 24, 21 });
	idle.PushBack({ 93, 5, 24, 21 });
	idle.speed = 0.01f;

	walk_right.PushBack({ 1,  35, 26, 21 });
	walk_right.PushBack({ 35, 35, 26, 21 });
	walk_right.PushBack({ 64, 35, 26, 21 });
	walk_right.PushBack({ 94, 35, 26, 21 });
	walk_right.speed = 0.01f;

	jump_right.PushBack({ 2, 66,  24, 21 });
	jump_right.PushBack({ 32, 66, 24, 21 });
	jump_right.PushBack({ 63, 66, 24, 21 });
	jump_right.speed = 0.01f;

	run_right.PushBack({ 3,  94, 23, 21 });
	run_right.PushBack({ 32, 94, 23, 21 });
	run_right.PushBack({ 62, 94, 23, 21 });
	run_right.PushBack({ 92, 94, 23, 21 });
	run_right.speed = 0.01f;
	
	fly_right.PushBack({ 0,  121,  30, 30 });
	fly_right.PushBack({ 30, 121, 30, 30 });
	fly_right.PushBack({ 60, 121, 30, 30 });
	fly_right.speed = 0.01f;

	//Left---------------------------------------
	
	walk_left.PushBack({ 4,  155, 23, 22 });
	walk_left.PushBack({ 31, 155, 23, 22 });
	walk_left.PushBack({ 63, 155, 23, 22 });
	walk_left.PushBack({ 91, 155, 23, 22 });
	walk_left.speed = 0.01f;

	jump_left.PushBack({ 5,  185, 23, 22 });
	jump_left.PushBack({ 30, 185, 23, 22 });
	jump_left.PushBack({ 60, 185, 23, 22 });
	jump_left.speed = 0.01f;

	run_left.PushBack({ 6,  215, 23, 21 });
	run_left.PushBack({ 34, 215, 23, 21 });
	run_left.PushBack({ 65, 215, 23, 21 });
	run_left.PushBack({ 94, 215, 23, 21 });
	run_left.speed = 0.01f;

	fly_left.PushBack({ 0,  240,  30, 30 });
	fly_left.PushBack({ 30, 240,  30, 30 });
	fly_left.PushBack({ 60, 240,  30, 30 });
	fly_left.speed = 0.01f;





}

Player::~Player()
{
}

bool Player::Awake(pugi::xml_node& config)
{
	position.create(160, 512);
	velocity.create(0, 0);
	//TODO SERGIO 2: Init start position

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
	//TODO SERGIO 3:
	//Create a function to change lvls (F1, F2, etc...)
	//Remember use Setzero();

	Input();
	processPos();
	processGravity();
	ReturnToZero();
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
			//velocity.x -= 0.001f;
		}
		if (!isFly)
			state = W_LEFT;
		else if (state == FLY_RIGHT)
			state = FLY_LEFT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		direction = NON;
		//returntoZero = true;
		//goZero = LEFT;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		direction = LEFT;
		if (App->map->MovementCost(position.x, position.y, 30, 30, direction))
		{
			position.x -= 0.5f;
			//velocity.x -= 0.05f;
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
			//velocity.x += 0.001f;
		}
		if (!isFly)state = W_RIGHT;
		else if (state == FLY_LEFT)
			state = FLY_RIGHT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		direction = NON;
		//returntoZero = true;
		//goZero = RIGHT;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		direction = RIGHT;
		if (App->map->MovementCost(position.x, position.y, 30, 30, direction))
		{
			position.x += 0.5f;
			velocity.x += 0.05f;
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

void Player::ReturnToZero()
{
	if (returntoZero && goZero != NON)
	{
		if (goZero == LEFT)
		{
			velocity.x += 0.004f;
			if (velocity.x <= 0.1f && velocity.x >= -0.1f)
			{
				velocity.x = 0;
				goZero = NON;
				returntoZero = false;
			}
		}
		else
		{
			velocity.x -= 0.004f;
			if (velocity.x <= 0.1f && velocity.x >= -0.1f)
			{
				velocity.x = 0;
				goZero = NON;
				returntoZero = false;
			}
		}
	}
}

void Player::Setzero()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Player::processPos()
{
	//TODO SERGIO 4: CAP MAX VELOCITY
	//if(velocity.) 
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
