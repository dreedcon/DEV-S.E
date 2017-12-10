#include "UI_Element.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "p2Log.h"
#include "UI_Text_Box.h"
#include "UI_Button.h"
#include "UI_Scroll.h"

//Constructors
Ui_Element::Ui_Element(const SDL_Rect& box, UI_TYPE ui_type, bool IsActive) :box(box), ui_type(ui_type), IsActive(IsActive) {}

Ui_Element::Ui_Element(const Ui_Element* copy) : box(copy->box), ui_type(copy->ui_type), IsActive(copy->IsActive) {}

Ui_Element::Ui_Element() : box({0,0,0,0}), ui_type(UNDEFINED), IsActive(false) {}

//Destructor
Ui_Element::~Ui_Element()
{

}


// Game Loop ==============================================
bool Ui_Element::Update()
{
	HandleInput();
	//input_type_up = GetInputType();
	//Childs Update
	UpdateChilds();

	return true;
}

bool Ui_Element::UpdateChilds()
{

	bool ret = true;

	p2List_item<Ui_Element*>* item = childs.start;
	while (item) {

		if (item->data->IsActive)
			ret = item->data->Update();

		item = item->next;
	}
	return ret;

}

bool Ui_Element::CleanUp()
{
	CleanUpChilds();
	return true;

}

bool Ui_Element::CleanUpChilds()
{
	bool ret = true;

	p2List_item<Ui_Element*>* item = childs.start;
	while (item) {

		ret = item->data->CleanUp();
		childs.del(item);

		item = item->next;
	}

	return ret;
}

void Ui_Element::Draw(bool debug)const
{
	DrawChilds(debug);
}

void Ui_Element::DrawAt(int x, int y) const
{
}

void Ui_Element::DrawChilds(bool debug) const
{
	p2List_item<Ui_Element*>* item = childs.start;
	while (item) 
	{
		if (item->data->ui_type == BUTTON && item->data->parent->ui_type == SCROLL)
		{

		}
		else
		{
			if (item->data->parent->ui_type == SCROLL && item->data->ui_type == TEXT_BOX)
			{

			}
			else
			{
				if (item->data->IsActive)
					item->data->Draw(debug);
			}

		}

		item = item->next;
	}
}

// Functionality ==========================================
void Ui_Element::MoveBox(int x_vel, int y_vel)
{
	box.x += x_vel;
	box.y += y_vel;

	p2List_item<Ui_Element*>* item = childs.start;
	while (item) 
	{
		if (item->data->parent->ui_type == SCROLL)
		{

		}
		else
		{
			item->data->MoveBox(x_vel, y_vel);
		}
		item = item->next;
	}
}

bool Ui_Element::MouseIsIn() const
{	
	int x_pos, y_pos;

	App->input->GetMousePosition(x_pos, y_pos);
	if (this->parent != NULL)
	{
		if (this->parent->ui_type == SCROLL && this->ui_type == BUTTON ||
			this->parent->ui_type == SCROLL && this->ui_type == TEXT_BOX)
		{
			return ((box.x + this->parent->box.x < x_pos && (box.x + this->parent->box.x + box.w) > x_pos) && (box.y + this->parent->box.y < y_pos && (box.y + this->parent->box.y + box.h) > y_pos));
		}
	}
	return ((box.x < x_pos && (box.x + box.w) > x_pos) && (box.y < y_pos && (box.y + box.h) > y_pos));
}

bool Ui_Element::MouseIsIn(int x, int y) const
{
	int x_pos, y_pos;

	App->input->GetMousePosition(x_pos, y_pos);

	return ((box.x + x < x_pos && (box.x + x + box.w) > x_pos) && (box.y + y < y_pos && (box.y + y + box.h) > y_pos));
}

bool Ui_Element::MouseIsIn(const SDL_Rect* box_rect) const
{
	int x_pos, y_pos;

	App->input->GetMousePosition(x_pos, y_pos);

	return((box_rect->x <= x_pos) && ((box_rect->w + box_rect->x) >= x_pos && (box_rect->y <= y_pos) && ((box_rect->y + box_rect->h) >= y_pos)));
	 
}

void Ui_Element::ResizeBox(const iPoint & new_size)
{
	box.w = new_size.x;
	box.h = new_size.y;
}

void Ui_Element::SetBox(SDL_Rect newbox)
{
	box = newbox;
}

bool Ui_Element::RectIsIn(const SDL_Rect* box_rect, int x_vel, int y_vel, bool x_axis )const
{
	bool ret = false;
	bool ret_2 = false;
	
	
	if (x_axis == false)
	{
		ret = (box_rect->y <= box.y + y_vel && (box_rect->y + box_rect->h) >= (box.y + box.h + y_vel));
	}
	else
	{
		ret = (box_rect->y <= box.y + y_vel && (box_rect->y + box_rect->h) >= (box.y + box.h + y_vel));
		ret_2 = (box_rect->x <= box.x + x_vel && (box_rect->x + box_rect->w) >= (box.x + box.w + x_vel));

		if (ret && ret_2)
			ret = true;
		else
			ret = false;
	}
	return ret;
}

bool Ui_Element::Drag()
{
	//Get mouse left button state
	j1KeyState mouse_button_1 = App->input->GetMouseButtonDown(1);

	int x_motion = 0, y_motion = 0;
	App->input->GetMouseMotion(x_motion, y_motion);
	if (mouse_button_1 == KEY_IDLE)
	{
		return false;
	}

	if (MouseIsIn() == false && App->gui->ItemSelected == this && (mouse_button_1 == KEY_DOWN))
	{
		App->gui->ItemSelected = nullptr;
		return false;
	}

	else if (App->gui->ItemSelected == this && mouse_button_1 == KEY_REPEAT)
	{
		//parent->childs.MovetoUP(this);
		this->MoveBox(x_motion, y_motion);
		LOG("%i - %i", x_motion, y_motion);
		return true;
	}

	else if (MouseIsIn() && App->gui->ItemSelected != this && mouse_button_1 == KEY_DOWN && App->gui->upper_element == this->layer)
	{
		App->gui->ItemSelected = this;
		return true;
	}
}

bool Ui_Element::GetActiveState() const
{
	return IsActive;
}

void Ui_Element::Activate()
{
	IsActive = true;
}

void Ui_Element::Desactivate()
{
	IsActive = false;
}

bool Ui_Element::Select()
{
	//Get mouse left button state
	j1KeyState mouse_button_1 = App->input->GetMouseButtonDown(1);
	//Return if theres no input
	if (mouse_button_1 == KEY_IDLE)
	{
		return false;
	}

	if (MouseIsIn() == false && App->gui->ItemSelected == this && (mouse_button_1 == KEY_DOWN))
	{
		App->gui->ItemSelected = nullptr;
		return false;
	}
	else if (MouseIsIn() && App->gui->ItemSelected != this && mouse_button_1 == KEY_DOWN && App->gui->upper_element == this->layer)
	{
		App->gui->ItemSelected = this;
		return true;
	}
	return false;
}

void Ui_Element::HandleInput()
{

}

void Ui_Element::AddChild(Ui_Element* child, uint start_layer)
{
	child->SetParent(this);
	child->layer = this->layer + 1 + start_layer;
	childs.add(child);
}

bool Ui_Element::Delete_Child(Ui_Element* child)
{
	return childs.del(childs.At(childs.find(child)));
}

bool Ui_Element::Delete_Child(uint index)
{
	return childs.del(childs.At(index));
}

Ui_Element* Ui_Element::SetParent(const Ui_Element* parent)
{
	if (parent != NULL)
	{
		if (parent->ui_type != SCROLL)
		{
			this->box.x += parent->box.x;
			this->box.y += parent->box.y;
		}
	}

	return this->parent = ((Ui_Element*)parent);
}

void Ui_Element::SetNumerTab(uint num)
{
	this->number_tab = num;
	App->gui->elementCanTab.add(this);
}

Ui_Element * Ui_Element::GetelementofTAB()
{
	p2List_item<Ui_Element*>*  item = App->gui->elementCanTab.start;
	for (int i = 0; i < App->gui->elementCanTab.count(); i++)
	{
		if (item->data->number_tab == App->gui->select_tab)
		{
			return item->data;
		}
		else
		{
			item = item->next;
		}
	}
	return NULL;
}


