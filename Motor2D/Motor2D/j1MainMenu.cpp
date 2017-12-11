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

	mainscene = App->gui->GenerateUI_Element(UI_TYPE::UNDEFINED);
	mainscene->SetBox({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h });
	mainscene->Activate();
	//mainscene->SetInputTarget(this);

	//test = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	//test->SetTextureRect({ 266, 194, 392, 426 });
	//test->AdjustBox();
	//test->Activate();
	//mainscene->AddChild(test, 10);

	Ui_img tex_on({ 0,0 }, { 5,107,225,75 });
	Ui_img tex_off({ 0,0 }, { 234,108,222,73 });
	Ui_img tex_over({ 0,0 }, { 459,106, 222,80 });

	button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button->Activate();
	button->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button->box = { 266, 194, 392, 426 };
	//button->box = { 200, 300, 220, 60 };

	play_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	play_button->Activate();
	button->AddChild(play_button, 10);
	play_button->setText_Font(App->font->font_Title);
	play_button->MoveBox(85, 15);
	play_button->SetString("Play");

	App->gui->PushScreen(mainscene);
	mainscene->AddChild(button, 30);

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
		App->scene->active = true;
		App->managerC->active = true;
		App->scene->Start();
		App->managerC->Start();
		play_button->Desactivate();
	/*	test->Desactivate();*/
		button->Desactivate();
	}

    //RETURN TO MAIN MENU --------------------------------------------------------
	if (button->button_state == UI_Button::BUTTON_STATE::ON)
	{
	App->scene->active = true;
	App->managerC->active = true;
	App->scene->Start();
	App->managerC->Start();
	play_button->Desactivate();
	//test->Desactivate();
	button->Desactivate();
	}

	int x, y, x_motion, y_motion;
	App->input->GetMousePosition(x, y);
	App->input->GetMouseMotion(x_motion, y_motion);
	App->gui->CalculateUpperElement(mainscene, 0);
	/*test->Drag();*/



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
