#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

#include "UI_Element.h"
#include "UI_Button.h"
#include "UI_IMG.h"
#include "UI_Scroll.h"
#include "UI_String.h"
#include "UI_Text_Box.h"


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	//Load Atlas
	atlas = App->tex->Load(atlas_file_name.GetString());

	//Load other textures if you want
	ui_textures.add(App->tex->Load("gui/anger2.png"));
	ui_textures.add(App->tex->Load("gui/tes.png"));

	viewport_box = { 0,0,0,0 };
	

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	bool ret = true;
	type_input = GetInputType();
	p2List_item<Ui_Element*>* item = screens.start;
	while (item) 
	{
		if (item->data->IsActive)
			ret = item->data->Update();

		item = item->next;
	}
	
	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	//Debug Mode ------------------------------------------
	if (type_input == INPUT_TYPE::INPUT_DEBUG && ItemSelected == nullptr)
	{
		debug = !debug;
	}

	// Update & draw the UI screens
	p2List_item<Ui_Element*>* item = screens.start;
	while (item) {

		if (item->data->IsActive)
			item->data->Draw(debug);

		item = item->next;
	}
	//SDL_Rect temp = { 0,0,500,500 };
	//App->render->Blit(atlas, 0, 0, &temp);

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	bool ret = true;
	p2List_item<Ui_Element*>* item = screens.end;
	p2List_item<Ui_Element*>* item_prev = nullptr;

	if (item != nullptr)item_prev = item->prev;
	while (item) {

		//CleanUp the item childs
		ret = item->data->CleanUp();
		//Delete all item data
		screens.del(item);

		item = item_prev;
		if(item_prev != nullptr)item_prev = item_prev->prev;

	}

	return true;
}




// =================================================================
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

SDL_Texture * j1Gui::Get_UI_Texture(uint tex_id)
{
	if (tex_id > ui_textures.count() - 1)
	{
		return nullptr;
	}
	
	return ui_textures.At(tex_id)->data;
}

uint j1Gui::PushScreen(const Ui_Element* new_screen)
{
	//Add new Screen in the list
	screens.add((Ui_Element*)new_screen);
	return screens.count();
}

uint j1Gui::CalculateUpperElement(const Ui_Element* parent, uint layer) const
{

	p2List_item<Ui_Element*>* item = parent->childs.start;

	while (item) 
	{
		
		layer = CalculateUpperElement(item->data,layer);

		if (item->data->layer > layer && item->data->IsActive && item->data->MouseIsIn())
		{
			layer = item->data->layer;
		}
		
		item = item->next;

	}

	upper_element = layer;
	return uint(layer);
}

Ui_Element* j1Gui::GenerateUI_Element(UI_TYPE element_type)
{
	Ui_Element* new_element = nullptr;
	switch (element_type)
	{
	case UI_TYPE::UNDEFINED:
		new_element = new Ui_Element();
		break;

	case UI_TYPE::BUTTON:
		new_element = new UI_Button();
		break;

	case UI_TYPE::TEXT_BOX:
		new_element = new UI_Text_Box();
		break;

	case UI_TYPE::STRING:
		new_element = new UI_String();
		break;

	case UI_TYPE::IMG:
		new_element = new Ui_img();
		break;

	case UI_TYPE::SCROLL:
		new_element = new UI_Scroll();
		break;
	}

	return new_element;
}

Ui_Element* j1Gui::GetActiveScreen() const
{
	p2List_item<Ui_Element*>* item = screens.start;
	while (item)
	{
		if (item->data->GetActiveState())return item->data;
		item = item->next;
	}
	return nullptr;
}

INPUT_TYPE j1Gui::GetInputType()
{
	INPUT_TYPE type = INPUT_TYPE::INPUT_NONDEF;

	j1KeyState mouse_key_1 = App->input->GetMouseButtonDown(1);

	if (mouse_key_1 == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_CLICK_LEFT;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_UP;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_DOWN;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_LEFT;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_RIGHT;
	}
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_DEBUG;
	}
	if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_BACKSPACE;
	}
	if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
	{
		type = INPUT_TYPE::INPUT_DELETE_INPUT;
	}
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		if (select_tab == elementCanTab.count())
		{
			select_tab = 1;
		}
		else
		{
			select_tab += 1;
		}
		type = INPUT_TYPE::INPUT_TAB;
	}
	return type;
}