#include "j1MainMenu.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "ManagerCriatures.h"

#include "UI_Element.h"
#include "UI_Button.h"
#include "UI_IMG.h"
#include "UI_Scroll.h"
#include "UI_String.h"
#include "UI_Text_Box.h"


j1MainMenu::j1MainMenu() : j1Module()
{
	name.create("mainmenu");
}


j1MainMenu::~j1MainMenu()
{
}

bool j1MainMenu::Awake(pugi::xml_node & conf)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool j1MainMenu::Start()
{
	App->scene->active = false;
	background = App->tex->Load("textures/atlas_kirby.png");
	App->audio->PlayMusic("audio/music/Music_LVL1.ogg");
	return true;
}

bool j1MainMenu::PreUpdate()
{
	return true;
}

bool j1MainMenu::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
	{

	}
	// RETURN TO MAIN MENU --------------------------------------------------------
	//if (button->button_state == UI_Button::BUTTON_STATE::ON)
	//{
	//App->scene->active = true;
	//App->managerC->active = true;
	//App->scene->Start();
	//App->managerC->Start();
	//}
	return true;
}

bool j1MainMenu::PostUpdate()
{
	App->render->Blit(background, 0, 0, NULL);
	return true;
}

bool j1MainMenu::CleanUp()
{
	return true;
}
