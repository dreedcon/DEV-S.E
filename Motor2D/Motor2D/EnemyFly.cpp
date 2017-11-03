#include "EnemyFly.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "Player.h"


EnemyFly::EnemyFly() : Criature()
{
	name.create("enemyfly");

	idle.PushBack({ 10,  14, 30, 29 });
	idle.PushBack({ 73,  14, 32, 31 });
	idle.PushBack({ 134, 11, 32, 32 });
	idle.speed = AnimationSpeed4;

	idle_left.PushBack({ 13,193, 30, 29});
	idle_left.PushBack({ 75,192, 32, 28});
	idle_left.PushBack({ 151,192, 32,31});
	idle_left.speed = AnimationSpeed4;

	//Left---------------------------------------

	fly_right.PushBack({ 9,  63, 36, 48 });
	fly_right.PushBack({ 70, 64, 36, 46 });
	fly_right.PushBack({ 127,66, 39, 32 });
	fly_right.PushBack({ 190,75, 39, 32 });
	fly_right.PushBack({ 251,76, 37, 30 });
	fly_right.speed = AnimationSpeed4;

	fly_left.PushBack({ 13, 245, 36, 48 });
	fly_left.PushBack({ 72, 245, 36, 46 });
	fly_left.PushBack({ 129,244, 39, 32 });
	fly_left.PushBack({ 190,251, 39, 32 });
	fly_left.PushBack({ 250,252, 37, 30 });
	fly_left.speed = AnimationSpeed4;
	
	//Death--------------------------------------
	dead.PushBack({ 12, 132, 31, 29 });
	dead.PushBack({ 72, 132, 31, 31 });
	dead.PushBack({ 132,132, 32, 31 });
	dead.PushBack({ 194,133, 26, 32 });
	dead.PushBack({ 254,136, 32, 29 });
	dead.PushBack({ 318,139, 32, 23 });
	dead.speed = AnimationSpeedDead;
}


EnemyFly::~EnemyFly()
{
}

bool EnemyFly::Awake()
{
	position.create(300, 354);
	velocity.create(0, 0);
	return true;
}

bool EnemyFly::Start()
{
	graphics = App->tex->Load("textures/Fly_enemy.png");
	current_animation = &idle;
	state = IDLE;
	return true;
}

bool EnemyFly::PreUpdate()
{
	return true;
}

bool EnemyFly::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
	{
		state = RUN_LEFT;
	}
	else
	{
		state = IDLE;
	}
	return true;
}

void EnemyFly::processPos()
{
}

void EnemyFly::processGravity()
{
}

void EnemyFly::ReturnToZero()
{
}

void EnemyFly::Draw()
{
	switch (state)
	{
	case IDLE:
	{
		current_animation = &idle;
		break;
	}
	case RUN_LEFT:
	{
		current_animation = &fly_left;
		break;
	}
	case RUN_RIGHT:
	{
		current_animation = &fly_right;
		break;
	}
	case DEAD:
	{
		current_animation = &dead;
		break;
	}
	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x / 2, position.y / 2 - 10, &r, 2);
}

bool EnemyFly::PostUpdate()
{
	Draw();
	return true;
}

bool EnemyFly::Load(pugi::xml_node &)
{
	return true;
}

bool EnemyFly::Save(pugi::xml_node &) const
{
	return true;
}

int EnemyFly::GetDirection() const
{
	return 0;
}

fPoint * EnemyFly::Getposition() const
{
	return nullptr;
}

bool EnemyFly::CleanUp()
{
	return true;
}