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
	background = App->tex->Load("textures/Background.png");
	App->audio->PlayMusic("audio/music/Music_LVL1.ogg");

	mainscene = App->gui->GenerateUI_Element(UI_TYPE::UNDEFINED);
	mainscene->SetBox({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h });
	mainscene->Activate();
	//mainscene->SetInputTarget(this);

	//Test Window
	//test = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	//test->SetTextureRect({ 266, 194, 392, 426 });
	//test->AdjustBox();
	//test->Activate();
	//mainscene->AddChild(test, 10);

	//Play Button
	Ui_img tex_on({ 0,0 }, { 5,107,225,75 });
	Ui_img tex_off({ 0,0 }, { 234,108,222,73 });
	Ui_img tex_over({ 0,0 }, { 459,106, 222,80 });

	button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button->Activate();
	button->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button->box = {417, 550, 225, 75};
	
	play_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	play_button->Activate();
	button->AddChild(play_button, 10);
	play_button->setText_Font(App->font->font_Title);
	play_button->MoveBox(85, 15);
	play_button->SetString("Play");

	//exit
	button2 = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button2->Activate();
	button2->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button2->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button2->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button2->box = { 750, 400, 225, 75 };

	Exit_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Exit_button->Activate();
	button2->AddChild(Exit_button, 10);
	Exit_button->setText_Font(App->font->font_Title);
	Exit_button->MoveBox(85, 15);
	Exit_button->SetString("Exit");

	//Continue
	button3 = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button3->Activate();
	button3->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button3->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button3->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button3->box = {160, 550, 225, 75 };

	Continue_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Continue_button->Activate();
	button3->AddChild(Continue_button, 10);
	Continue_button->setText_Font(App->font->font_Title);
	Continue_button->MoveBox(55, 15);
	Continue_button->SetString("Continue");

	//Settings
	button4 = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button4->Activate();
	button4->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button4->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button4->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button4->box = { 675, 550, 225, 75 };

	settings_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	settings_button->Activate();
	button4->AddChild(settings_button, 10);
	settings_button->setText_Font(App->font->font_Title);
	settings_button->MoveBox(60, 15);
	settings_button->SetString("Settings");

	//Credits
	button5 = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button5->Activate();
	button5->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button5->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button5->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button5->box = {50, 400, 225, 75 };

	Credits_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Credits_button->Activate();
	button5->AddChild(Credits_button, 10);
	Credits_button->setText_Font(App->font->font_Title);
	Credits_button->MoveBox(65, 15);
	Credits_button->SetString("Credits");

	//AddChilds
	mainscene->AddChild(button, 30);
	mainscene->AddChild(button2, 30);
	mainscene->AddChild(button3, 30);
	mainscene->AddChild(button4, 30);
	mainscene->AddChild(button5, 30);

	App->gui->PushScreen(mainscene);
	
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
		mainscene->Desactivate();
	}

    //Button Funcionalities --------------------------------------------------------
	if (button->button_state == UI_Button::BUTTON_STATE::ON)//Play
	{
		App->scene->active = true;
		App->managerC->active = true;
		App->scene->Start();
		App->managerC->Start();
		mainscene->Desactivate();
	}

	if (button2->button_state == UI_Button::BUTTON_STATE::ON)//Exit
	{
		return false;
	}

	if (button3->button_state == UI_Button::BUTTON_STATE::ON)//Continue
	{
		
	}

	if (button4->button_state == UI_Button::BUTTON_STATE::ON)//Settings
	{

	}


	int x, y, x_motion, y_motion;
	App->input->GetMousePosition(x, y);
	App->input->GetMouseMotion(x_motion, y_motion);
	App->gui->CalculateUpperElement(mainscene, 0);




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
