#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1MainMenu.h"
#include "ManagerCriatures.h"

#include "UI_Element.h"
#include "UI_Button.h"
#include "UI_IMG.h"
#include "UI_Scroll.h"
#include "UI_String.h"
#include "UI_Text_Box.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->mainmenu->active = false;
	mainscene->Activate();
	playtime.Start();
	App->audio->PlayMusic("audio/music/Music_LVL1.ogg");

	App->map->Load("LVL3.tmx");

	//Check Lvl
	SetLevelInfo(App->managerC->player->actualvl);

	return true;
}

void j1Scene::LoadUi()
{
	mainscene = App->gui->GenerateUI_Element(UI_TYPE::UNDEFINED);
	mainscene->SetBox({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h });
	mainscene->Activate();
	//mainscene->SetInputTarget(this);

	imageLVL = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	imageLVL->SetTextureRect({ 3, 196, 226, 88 });
	imageLVL->AdjustBox();
	imageLVL->Activate();
	imageLVL->box = { 10,650,0,0 };
	mainscene->AddChild(imageLVL, 10);

	UI_String Text({ 0,0,0,0 }, "LEVEL 1", App->font->font_Title);
	actualvl = (UI_Text_Box*)App->gui->GenerateUI_Element(UI_TYPE::TEXT_BOX);
	actualvl->box = { 20,20,20,20 };
	actualvl->Text_entered = Text;
	actualvl->Activate();
	imageLVL->AddChild(actualvl, 20);

	int marge = 0;
	for (int i = 0; i < PlayerLifes; i++)
	{
		UI_Button* life = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
		SetLife(life, marge);
		lifes.add(life);
		mainscene->AddChild(life, 30);
	}

	Ui_img button_on({ 0,0 }, { 3, 196, 226, 88 });
	Ui_img button_off({ 0,0 }, { 6, 293, 232, 87 });
	Ui_img button_over({ 0,0 }, { 453,7,232,87 });
	
	buttonReturnMenu = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	buttonReturnMenu->Activate();
	buttonReturnMenu->SetTextures_button(UI_Button::BUTTON_STATE::ON, button_on);
	buttonReturnMenu->SetTextures_button(UI_Button::BUTTON_STATE::OFF, button_off);
	buttonReturnMenu->SetTextures_button(UI_Button::BUTTON_STATE::OVER, button_over);
	buttonReturnMenu->box = { 780,680,230,87 };
	mainscene->AddChild(buttonReturnMenu, 40);
	Options = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	Options->Activate();
	Options->setText_Font(App->font->font_Title);
	Options->MoveBox(20, 15);
	Options->SetString("Settings");
	buttonReturnMenu->AddChild(Options, 10);

	Ui_img button_onOptions({ 0,0 }, { 3, 915, 233,86 });
	Ui_img button_overOptions({ 0,0 }, { 238,827,233,86 });
	Ui_img button_offOptions({ 0,0 }, { 3, 826, 233,86 });

	O_imgButtonReturn = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	O_imgButtonReturn->Desactivate();
	O_imgButtonReturn->SetTextures_button(UI_Button::BUTTON_STATE::ON, button_onOptions);
	O_imgButtonReturn->SetTextures_button(UI_Button::BUTTON_STATE::OFF, button_offOptions);
	O_imgButtonReturn->SetTextures_button(UI_Button::BUTTON_STATE::OVER, button_overOptions);
	O_imgButtonReturn->box = { 780,590,230,87 };
	mainscene->AddChild(O_imgButtonReturn, 50);
	S_imgButtonReturn = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	S_imgButtonReturn->Activate();
	S_imgButtonReturn->setText_Font(App->font->font_Title);
	S_imgButtonReturn->MoveBox(63, 10);
	S_imgButtonReturn->SetString("Go Menu");
	O_imgButtonReturn->AddChild(S_imgButtonReturn, 10);

	O_imgLoad = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	O_imgLoad->Desactivate();
	O_imgLoad->SetTextures_button(UI_Button::BUTTON_STATE::ON, button_onOptions);
	O_imgLoad->SetTextures_button(UI_Button::BUTTON_STATE::OFF, button_offOptions);
	O_imgLoad->SetTextures_button(UI_Button::BUTTON_STATE::OVER, button_overOptions);
	O_imgLoad->box = { 780,506,230,87 };
	mainscene->AddChild(O_imgLoad, 50);
	S_imgLoad = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	S_imgLoad->Activate();
	S_imgLoad->setText_Font(App->font->font_Title);
	S_imgLoad->MoveBox(83, 15);
	S_imgLoad->SetString("Load");
	O_imgLoad->AddChild(S_imgLoad, 10);

	O_imgSave = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	O_imgSave->Desactivate();
	O_imgSave->SetTextures_button(UI_Button::BUTTON_STATE::ON, button_onOptions);
	O_imgSave->SetTextures_button(UI_Button::BUTTON_STATE::OFF, button_offOptions);
	O_imgSave->SetTextures_button(UI_Button::BUTTON_STATE::OVER, button_overOptions);
	O_imgSave->box = { 780,422,230,87 };
	mainscene->AddChild(O_imgSave, 50);
	S_imgSave = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	S_imgSave->Activate();
	S_imgSave->setText_Font(App->font->font_Title);
	S_imgSave->MoveBox(83, 15);
	S_imgSave->SetString("Save");
	O_imgSave->AddChild(S_imgSave, 10);

	clock = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	clock->SetTextureRect({ 2, 634, 170, 87 });
	clock->AdjustBox();
	clock->Activate();
	clock->box = { 430,20,20,20 };
	mainscene->AddChild(clock, 60);
	clocktime = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	clocktime->Activate();
	clocktime->setText_Font(App->font->font_Title);
	clocktime->MoveBox(75,25);
	clocktime->SetString("00:00");
	clock->AddChild(clocktime, 10);

	//Ui_img scroll_item({ 0,0 }, { 900, 314, 68, 54 });
	//scroll_item.AdjustBox();
	//Ui_img scroll_back({ 0,0 }, { 0, 290, 300, 169 });
	//scroll_back.AdjustBox();

	//scroll = (UI_Scroll*)App->gui->GenerateUI_Element(UI_TYPE::SCROLL);
	//scroll->box = { 50, 150, 300, 160 };
	//scroll->Activate();
	//scroll->SetContentWidow({ 0,0,300,160 });
	//scroll->SetScroll_back(scroll_back);
	//scroll->haveScroll_bar = true;
	//scroll->SetScroll_item(scroll_item);
	//scroll->SetTypeScroll(SCROLL_TYPE::VERTICAL);
	//mainscene->AddChild(scroll, 80);
	//test = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	//test->SetTextureRect({ 3, 196, 226, 88 });
	//test->AdjustBox();
	//test->Activate();
	//test->box = { 0,0,0,0 };
	//scroll->AddScrollItem(test, 10);
	

	numlifesactive = PlayerLifes;
	App->gui->PushScreen(mainscene);
}

void j1Scene::NewGame()
{
	p2List_item<UI_Button*>* item = lifes.start;
	for (int i = 0; i < PlayerLifes; i++)
	{
		item->data->button_state = UI_Button::BUTTON_STATE::ON;
		item = item->next;
	}
	playtime.Start();
	numlifesactive = PlayerLifes;
}

void j1Scene::SetLevelInfo(int lvl)
{
	if (lvl == 0)
	{
		actualvl->SetText("LEVEL 1");
	}
	else
	{
		actualvl->SetText("LEVEL 2");
	}
}

void j1Scene::SetLife(UI_Button* life, int& number)
{
	Ui_img tex_on({ 0,0 }, { 450,732,30,30 });
	Ui_img tex_off({ 0,0 }, { 450,766,31,29 });
	Ui_img tex_over({ 0,0 }, { 0,0, 0,0 });
	life->Activate();
	life->SetInteractive(false);
	life->button_state = UI_Button::BUTTON_STATE::ON;
	life->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	life->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	life->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	life->box = { 800 + number, 20, 220, 60 };
	number += 35;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	if (buttonReturnMenu->button_state == UI_Button::BUTTON_STATE::ON && goOpen)//Exit
	{
		if (settingOpen == false)
		{
			O_imgButtonReturn->Activate();
			O_imgLoad->Activate();
			O_imgSave->Activate();
			settingOpen = true;
		}
		else if (settingOpen == true)
		{
			O_imgButtonReturn->Desactivate();
			O_imgLoad->Desactivate();
			O_imgSave->Desactivate();
			settingOpen = false;
		}
		goOpen = false;
	}
	if (buttonReturnMenu->button_state != UI_Button::BUTTON_STATE::ON)
	{
		goOpen = true;
	}

	// Clock time

	_itoa_s((int)playtime.ReadSec(), buffer, 10);
	clocktime->SetString(buffer);

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	int x, y, x_motion, y_motion;
	App->input->GetMousePosition(x, y);
	App->input->GetMouseMotion(x_motion, y_motion);
	App->gui->CalculateUpperElement(mainscene, 0);

	/*scroll->MoveScroll(x_motion, y_motion);*/

	//test->Drag();
	//text->Drag();
	//Input_get(App->gui->type_input);

	//if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	App->render->camera.y -= 10;

	//if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	App->render->camera.y += 10;

	//if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	App->render->camera.x -= 10;



	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
	{
		App->audio->volume += 10;
		App->audio->Changevolume(App->audio->volume);
	}


	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
	{
		App->audio->volume -= 10;
		App->audio->Changevolume(App->audio->volume);
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->Load();

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->Save();



	p2SString title("Map:%dx%d Tiles : %dx%d Tilesets : %d", App->map->mapdata.width, App->map->mapdata.height, App->map->mapdata.tile_width, App->map->mapdata.tile_height, App->map->mapdata.tilesets.count());


	//App->map->Draw();
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;
	App->map->Draw(-1);
	App->map->Draw(0);

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		App->managerC->player->lifes--;

	if (App->managerC->player->lifes < numlifesactive)
	{
		p2List_item<UI_Button*>* item = lifes.start;
		for (int i = 0; i < PlayerLifes; i++)
		{
			if (App->managerC->player->lifes == i)
			{
				item->data->button_state = UI_Button::BUTTON_STATE::OFF;
				numlifesactive--;
			}
			item = item->next;
		}
	}
	if (numlifesactive <= 0)
	{
		App->map->CleanUp();
		App->mainmenu->active = true;
		App->mainmenu->Start();
		App->managerC->DeleteAllEnemies();
		App->managerC->active = false;
	}

	if (O_imgButtonReturn->button_state == UI_Button::BUTTON_STATE::ON)
	{
		O_imgButtonReturn->Desactivate();
		O_imgLoad->Desactivate();
		O_imgSave->Desactivate();
		settingOpen = false;
		O_imgButtonReturn->button_state = UI_Button::BUTTON_STATE::OFF;
		O_imgLoad->button_state = UI_Button::BUTTON_STATE::OFF;
		O_imgSave->button_state = UI_Button::BUTTON_STATE::OFF;
		App->map->CleanUp();
		App->mainmenu->active = true;
		App->mainmenu->Start();
		App->managerC->DeleteAllEnemies();
		App->managerC->active = false;
	}

	if (O_imgLoad->button_state == UI_Button::BUTTON_STATE::ON)
	{
		O_imgLoad->button_state = UI_Button::BUTTON_STATE::OFF;
		App->Load();
	}

	if (O_imgSave->button_state == UI_Button::BUTTON_STATE::ON)
	{
		O_imgSave->button_state = UI_Button::BUTTON_STATE::OFF;
		App->Save();
	}
	//if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		//ret = false;

	// RETURN TO MAIN MENU --------------------------------------------------------
	//if (button->button_state == UI_Button::BUTTON_STATE::ON)
	//{
	//	App->map->CleanUp();
	//	App->mainmenu->active = true;
	//	App->mainmenu->Start();
	//	App->managerC->DeleteAllEnemies();
	//	App->managerC->active = false;
	//}

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void j1Scene::Input_get(INPUT_TYPE type)
{
	type = App->gui->type_input;
	//if (type == RIGHT || type == LEFT || type == DOWN || type == UP)
	//{
	//	if (element_tab->ui_type == IMG && App->gui->ItemSelected == element_tab)
	//	{
	//		MoveSelector(type);
	//	}
	//}
	//if (type == TAB)
	//{
	//	App->gui->ItemSelected = element_tab->GetelementofTAB();
	//	element_tab = App->gui->ItemSelected;
	//}
	//if (type == CLICK_LEFT)
	//{
	//	if (button->button_state == ON)
	//	{
	//		test_n2->IsActive = !test_n2->IsActive;
	//	}
	//}
}

void j1Scene::MoveSelector(INPUT_TYPE type)
{
	//if (App->gui->ItemSelected == element_tab)
	//{
	//	if (type == RIGHT)
	//	{
	//		element_tab->MoveBox(20, 0);
	//	}
	//	if (type == LEFT)
	//	{
	//		element_tab->MoveBox(-20, 0);
	//	}
	//	if (type == DOWN)
	//	{
	//		element_tab->MoveBox(0, 20);
	//	}
	//	if (type == UP)
	//	{
	//		element_tab->MoveBox(0, -20);
	//	}
	//}
}