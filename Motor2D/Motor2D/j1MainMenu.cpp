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
	if (isLoadedUI == false)
	{
		App->scene->LoadUi();
		isLoadedUI = true;
	}
	App->scene->mainscene->Desactivate();
	App->scene->active = false;

	background = App->tex->Load("textures/Background.png");
	App->audio->PlayMusic("audio/music/Music_LVL1.ogg");
	App->audio->LoadFx("audio/fx/jump.wav"); //Fx---->1
	App->audio->LoadFx("audio/fx/float.wav"); //Fx----->2
	App->audio->LoadFx("audio/fx/dead.wav"); //Fx----->3
	App->audio->LoadFx("audio/fx/Button_click.wav"); //Fx----->4


	mainscene = App->gui->GenerateUI_Element(UI_TYPE::UNDEFINED);
	mainscene->SetBox({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h });
	mainscene->Activate();
	//mainscene->SetInputTarget(this);

	//Setting Window
	settings_window = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	settings_window->SetTextureRect({ 266, 194, 392, 426 });
	settings_window->AdjustBox();
	settings_window->box = { 300, 100, 397,425 };
	
	//Credits Window
	credits_window = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	credits_window->SetTextureRect({ 266, 194, 392, 426 });
	credits_window->AdjustBox();
	credits_window->box = { 300, 100, 397,425 };

	//Button states
	Ui_img tex_on({ 0,0 }, { 5,107,225,75 });
	Ui_img tex_off({ 0,0 }, { 234,108,222,73 });
	Ui_img tex_over({ 0,0 }, { 459,106, 222,80 });

	//Play Button
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
	play_button->MoveBox(46, 15);
	play_button->SetString("New Game");

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

	//Button states
	Ui_img close_button_on({ 0,0 }, { 854,860,33,32 });
	Ui_img close_button_off({ 0,0 }, { 854,860,33,32 });
	Ui_img close_button_over({ 0,0 }, { 854,860,33,32 });

	//Close Settings Button
	close_settings_button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	close_settings_button->Activate();
	close_settings_button->SetTextures_button(UI_Button::BUTTON_STATE::ON, close_button_on);
	close_settings_button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, close_button_off);
	close_settings_button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, close_button_over);
	close_settings_button->box = { 345,18,33,32 };
	settings_window->AddChild(close_settings_button, 10);

	//Close Credits Button
	close_credits_button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	close_credits_button->SetTextures_button(UI_Button::BUTTON_STATE::ON, close_button_on);
	close_credits_button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, close_button_off);
	close_credits_button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, close_button_over);
	close_credits_button->box = { 345,18,33,32 };
	credits_window->AddChild(close_credits_button, 20);

	//Web Button states
	Ui_img web_button_on({ 0,0 }, { 5,107,225,75 });
	Ui_img web_button_off({ 0,0 }, { 234,108,222,73 });
	Ui_img web_button_over({ 0,0 }, { 459,106, 222,80 });

	//elliot button Web Button
	elliot_button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	elliot_button->SetTextures_button(UI_Button::BUTTON_STATE::ON, web_button_on);
	elliot_button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, web_button_off);
	elliot_button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, web_button_over);
	elliot_button->box = {80,110,228,93 };
	credits_window->AddChild(elliot_button, 20);

	elliot_jimenez = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	elliot_jimenez->Activate();
	elliot_button->AddChild(elliot_jimenez, 10);
	elliot_jimenez->setText_Font(App->font->font_Title);
	elliot_jimenez->MoveBox(40, 15);
	elliot_jimenez->SetString("Elliot Jimenez");

	//sergio button Web Button
	sergio_button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	sergio_button->SetTextures_button(UI_Button::BUTTON_STATE::ON, web_button_on);
	sergio_button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, web_button_off);
	sergio_button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, web_button_over);
	sergio_button->box = {80,200,228,93 };
	credits_window->AddChild(sergio_button, 20);

	sergio_saez = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	sergio_saez->Activate();
	sergio_button->AddChild(sergio_saez, 10);
	sergio_saez->setText_Font(App->font->font_Title);
	sergio_saez->MoveBox(40, 15);
	sergio_saez->SetString("Sergio Saez");

	//Credits Word
	credits = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	credits->Activate();
	credits->setText_Font(App->font->font_Title);
	credits->MoveBox(140, 30);
	credits->SetString("Credits :");
	credits_window->AddChild(credits,20);

	//Web Button states
	Ui_img github_button_on({ 0,0 }, { 888,823,68,66});
	Ui_img github_button_off({ 0,0 }, { 888,823,68,66});
	Ui_img github_button_over({ 0,0 }, { 888,823,68,66});

	//Github Button
	github_button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	github_button->Activate();
	github_button->SetTextures_button(UI_Button::BUTTON_STATE::ON, github_button_on);
	github_button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, github_button_off);
	github_button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, github_button_over);
	github_button->box = {925, 690, 68, 66};

	//License Word
	Lincense = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Lincense->Activate();
	Lincense->setText_Font(App->font->font_Title);
	Lincense->MoveBox(100,290);
	Lincense->SetString("Apache License");
	credits_window->AddChild(Lincense, 20);

	Lincense2 = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Lincense2->Activate();
	Lincense2->setText_Font(App->font->font_Title);
	Lincense2->MoveBox(50, 320);
	Lincense2->SetString(" Version 2.0, January 2004");
	credits_window->AddChild(Lincense2, 20);

	Lincense3 = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Lincense3->Activate();
	Lincense3->setText_Font(App->font->font_Title);
	Lincense3->MoveBox(50, 350);
	Lincense3->SetString("www.apache.org/licenses/");
	credits_window->AddChild(Lincense3, 20);



	//AddChilds
	mainscene->AddChild(button, 30);
	mainscene->AddChild(button2, 30);
	mainscene->AddChild(button3, 30);
	mainscene->AddChild(button4, 30);
	mainscene->AddChild(button5, 30);
	mainscene->AddChild(github_button, 30);
	

	App->gui->PushScreen(mainscene);
	
	return true;
}

bool j1MainMenu::PreUpdate()
{
	return true;
}

bool j1MainMenu::Update(float dt)
{
	int x, y, x_motion, y_motion;
	App->input->GetMousePosition(x, y);
	App->input->GetMouseMotion(x_motion, y_motion);
	App->gui->CalculateUpperElement(mainscene, 0);

    //Button Funcionalities --------------------------------------------------------
	if (button->button_state == UI_Button::BUTTON_STATE::ON)//Play
	{
		App->scene->active = true;
		App->managerC->active = true;
		App->scene->Start();
		App->managerC->Start();
		App->managerC->NewGame();
		mainscene->Desactivate();
		if (isNewGame == false)
		{
			App->scene->NewGame();
		}
		isNewGame = false;
	}

	if (button2->button_state == UI_Button::BUTTON_STATE::ON)//Exit
	{
		return false;
	}

	if (button3->button_state == UI_Button::BUTTON_STATE::ON)//Continue
	{
		if (isNewGame == false)
		{
			App->scene->active = true;
			App->managerC->active = true;
			App->scene->Start();
			//App->managerC->Start();
			App->Load();
			mainscene->Desactivate();
		}
	}

	if (button4->button_state == UI_Button::BUTTON_STATE::ON)//Settings
	{	
		//Test Window Activate
		settings_window->Activate();
		close_settings_button->Activate();

		mainscene->AddChild(settings_window, 10);
	}

	if (button5->button_state == UI_Button::BUTTON_STATE::ON)//Settings
	{
		//Test Window Activate
		credits_window->Activate();
		close_credits_button->Activate();

		mainscene->AddChild(credits_window, 20);
	}


	if (close_settings_button->button_state == UI_Button::BUTTON_STATE::ON)
	{
		settings_window->Desactivate();
		close_settings_button->Desactivate();
		close_settings_button->button_state = UI_Button::BUTTON_STATE::OFF;
	}

	if (close_credits_button->button_state == UI_Button::BUTTON_STATE::ON)
	{
		credits_window->Desactivate();
		close_credits_button->Desactivate();
		close_credits_button->button_state = UI_Button::BUTTON_STATE::OFF;
	}

	if (elliot_button->button_state == UI_Button::BUTTON_STATE::ON)
	{
		ShellExecuteA(NULL, "open", "https://github.com/elliotjb", NULL, NULL, SW_SHOWNORMAL);
		elliot_button->button_state = UI_Button::BUTTON_STATE::OFF;
	}

	if (sergio_button->button_state == UI_Button::BUTTON_STATE::ON)
	{
		ShellExecuteA(NULL, "open", "https://github.com/dreedcon", NULL, NULL, SW_SHOWNORMAL);
		sergio_button->button_state = UI_Button::BUTTON_STATE::OFF;
	}

	if (github_button->button_state == UI_Button::BUTTON_STATE::ON)
	{
		ShellExecuteA(NULL, "open", "https://elliotjb.github.io/DEV-S.E/index.html", NULL, NULL, SW_SHOWNORMAL);
		github_button->button_state = UI_Button::BUTTON_STATE::OFF;
	}



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
