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
	App->audio->PlayMusic("audio/music/Music_LVL1.ogg");
	App->audio->LoadFx("audio/fx/jump.wav"); //Fx---->1
	App->audio->LoadFx("audio/fx/float.wav"); //Fx----->2
	App->audio->LoadFx("audio/fx/dead.wav"); //Fx----->3
	App->map->Load("LVL3.tmx");

	mainscene = App->gui->GenerateUI_Element(UI_TYPE::UNDEFINED);
	mainscene->SetBox({ 0,0,App->win->screen_surface->w, App->win->screen_surface->h });
	mainscene->Activate();
	//mainscene->SetInputTarget(this);

	test = (Ui_img*)App->gui->GenerateUI_Element(UI_TYPE::IMG);
	test->SetTextureRect({ 32, 538, 428, 459 });
	test->AdjustBox();
	test->Activate();
	mainscene->AddChild(test, 10);

	UI_String Text({ 0,0,0,0 }, "Enter Your Name", App->font->default);
	text = (UI_Text_Box*)App->gui->GenerateUI_Element(UI_TYPE::TEXT_BOX);
	text->box = { 0,0,100,50 };
	text->Text_entered = Text;
	text->Activate();
	mainscene->AddChild(text, 20);

	Ui_img tex_on({ 0,0 }, { 416, 172, 221, 60 });
	Ui_img tex_off({ 0,0 }, { 647,172,222,60 });
	Ui_img tex_over({ 0,0 }, { 5, 116, 220, 60 });

	button = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	button->Activate();
	button->SetTextures_button(UI_Button::BUTTON_STATE::ON, tex_on);
	button->SetTextures_button(UI_Button::BUTTON_STATE::OFF, tex_off);
	button->SetTextures_button(UI_Button::BUTTON_STATE::OVER, tex_over);
	button->box = { 200, 300, 220, 60 };

	continue_button = (UI_String*)App->gui->GenerateUI_Element(UI_TYPE::STRING);
	continue_button->Activate();
	button->AddChild(continue_button, 10);
	continue_button->setText_Font(App->font->font_Title);
	continue_button->MoveBox(35, 7);
	continue_button->SetString("CONTINUE");

	test->AddChild(button, 10);

	//mainscene->AddChild(button, 30);

	testbutton = (UI_Button*)App->gui->GenerateUI_Element(UI_TYPE::BUTTON);
	//testbutton->set

	App->gui->PushScreen(mainscene);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	int x, y, x_motion, y_motion;
	App->input->GetMousePosition(x, y);
	App->input->GetMouseMotion(x_motion, y_motion);
	App->gui->CalculateUpperElement(mainscene, 0);

	test->Drag();
	text->Drag();
	Input_get(App->gui->type_input);

	//if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	App->render->camera.y -= 10;

	//if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	App->render->camera.y += 10;

	//if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	App->render->camera.x -= 10;

	//if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//	App->render->camera.x += 10;

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