#include "EnemyNormal.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "Player.h"

EnemyNormal::EnemyNormal() : Criature()
{
	name.create("enemynormal");

	idle.PushBack({ 12,  16, 28, 30 });
	idle.PushBack({ 73,  19, 29, 29 });
	idle.PushBack({ 134, 19, 32, 28 });
	idle.PushBack({ 192, 19, 31, 28 });
	idle.PushBack({ 254, 18, 29, 29 });
	idle.PushBack({ 314, 17, 28, 30 });
	idle.speed = AnimationSpeed4;

	//Walk---------------------------------------

	run_left.PushBack({ 16, 72, 24, 30});
	run_left.PushBack({ 71, 74, 27, 28});
	run_left.PushBack({ 134,73, 27, 29});
	run_left.speed = AnimationSpeed4;

	run_right.PushBack({ 16, 194, 24, 30});
	run_right.PushBack({ 78, 196, 27, 28});
	run_right.PushBack({ 134,196, 27, 30});
	run_right.speed = AnimationSpeed4;

	//Death--------------------------------------
	dead.PushBack({ 14, 194, 22, 30});
	dead.PushBack({ 74, 196, 28, 28});
	dead.PushBack({ 134,194, 29, 22});
	dead.speed = AnimationSpeedDead;
}



EnemyNormal::~EnemyNormal()
{
}

bool EnemyNormal::Awake()
{
	position.create(200, 354);
	velocity.create(0, 0);
	return true;
}

bool EnemyNormal::Start()
{
	graphics = App->tex->Load("textures/Snow_Man.png");
	current_animation = &idle;
	state = IDLE;
	collision_feet = App->collision->AddCollider({ (int)position.x, (int)position.y, 50, 50 }, COLLIDER_ENEMY_NORMAL, this);
	return true;
}

bool EnemyNormal::PreUpdate()
{
	return true;
}

bool EnemyNormal::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
	{
		state = RUN_LEFT;
	}
	else
	{
		state = IDLE;
	}

	//Collision follow 
	collision_feet->SetPos(position.x, position.y - 25);
	return true;
}

void EnemyNormal::processPos()
{
}

void EnemyNormal::processGravity()
{
}

void EnemyNormal::ReturnToZero()
{
}

void EnemyNormal::Draw()
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
		current_animation = &run_left;
		break;
	}
	case RUN_RIGHT:
	{
		current_animation = &run_right;
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

bool EnemyNormal::PostUpdate()
{
	Draw();
	return true;
}

bool EnemyNormal::Load(pugi::xml_node &)
{
	return true;
}

bool EnemyNormal::Save(pugi::xml_node &) const
{
	return true;
}

int EnemyNormal::GetDirection() const
{
	return 0;
}

fPoint* EnemyNormal::Getposition() const
{
	return nullptr;
}

bool EnemyNormal::CleanUp()
{
	return true;
}
