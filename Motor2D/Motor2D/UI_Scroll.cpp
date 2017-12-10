#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "p2Log.h"
#include "UI_Scroll.h"
#include "UI_IMG.h"
#include "UI_String.h"
#include "UI_Button.h"
#include "UI_Text_Box.h"

//Constructors ============================================
UI_Scroll::UI_Scroll(const SDL_Rect& box, const SDL_Rect& itemsWindow, const Ui_img& ScrollItem, const Ui_img& ScrollBack, bool haveScroll_bar, SCROLL_TYPE Scroll_Type) :Ui_Element(box, SCROLL), itemsWindow(itemsWindow), ScrollItem(ScrollItem), ScrollBack(ScrollBack), haveScroll_bar(haveScroll_bar), Scroll_Type(Scroll_Type) {}

UI_Scroll::UI_Scroll(const UI_Scroll* copy) : Ui_Element(copy->box, SCROLL), itemsWindow(copy->itemsWindow), ScrollItem(copy->ScrollItem), ScrollBack(copy->ScrollBack), haveScroll_bar(copy->haveScroll_bar), Scroll_Type(copy->Scroll_Type) {}

UI_Scroll::UI_Scroll() : Ui_Element({ 0,0,0,0 }, SCROLL), itemsWindow({ 0,0,0,0 }), ScrollItem(), ScrollBack() {}


//Destructors =============================================
UI_Scroll::~UI_Scroll()
{

}


//Game Loop ===============================================
void UI_Scroll::Draw(bool debug) const
{
	//Draw Scroll & Content View Area Qwad -
	if (debug)
	{
		App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 150, 0);
		App->render->DrawQuad({ itemsWindow.x + box.x,itemsWindow.y + box.y,itemsWindow.w,itemsWindow.h }, 0, 50, 0);
		App->render->DrawQuad({ box.x + ScrollBack.box.x,box.y + ScrollBack.box.y,ScrollBack.box.w, ScrollBack.box.h }, 90, 20, 0);
		App->render->DrawQuad({ box.x + ScrollItem.box.x,box.y + ScrollItem.box.y,ScrollItem.box.w, ScrollItem.box.h }, 90, 80, 110);
	}

	//Draw the scroll img ------------------

	if (haveScroll_bar)
	{
		ScrollBack.DrawAt(box.x, box.y);
		ScrollItem.DrawAt(box.x, box.y);
	}
	//ScrollBack.DrawAt(box.x, box.y);


	
	//Draw the items -----------------------
	SDL_Rect view_port = { itemsWindow.x + box.x, itemsWindow.y + box.y, itemsWindow.w,itemsWindow.h };
	App->gui->viewport_box = view_port;
	SDL_RenderSetViewport(App->render->renderer,&view_port);
	p2List_item<Ui_Element*>* item = Items.start;
	while (item) 
	{
		item->data->Draw(debug);
		item = item->next;
	}
	SDL_RenderSetViewport(App->render->renderer,NULL);
	
	//Draw Scroll Childs -------------------
	DrawChilds(debug);
}

bool UI_Scroll::Update()
{
	p2List_item<Ui_Element*>*  item = Items.start;

	while (item)
	{
		//item->data->MoveBox(x_desp, y_desp);
		item->data->HandleInput();
		item = item->next;
	}
	return true;
}

void UI_Scroll::HandleInput()
{	
}



// Functionality =========================================
bool UI_Scroll::MoveScroll(int mouse_x_motion, int mouse_y_motion)
{
	//Get mouse left button state
	j1KeyState mouse_button_1 = App->input->GetMouseButtonDown(1);

	//Select the Scroll Item ----------
	if (ScrollItem.MouseIsIn(box.x, box.y) && mouse_button_1 == KEY_DOWN && App->gui->upper_element == this->layer)
	{
		ScrollSelected = true;
		App->gui->ItemSelected = this;
	}

	//Unselect the Scroll Item --------
	else if (ScrollSelected && mouse_button_1 == KEY_UP)
	{
		ScrollSelected = false;
	}

	//Drag the Scroll Item ------------
	if (ScrollSelected)
	{
		if (ScrollItem.RectIsIn(&ScrollBack.box, mouse_x_motion, mouse_y_motion) == false)
		{
			//Put the Scroll Item at the limit 
			if (mouse_y_motion < 0)
			{
				mouse_y_motion = ScrollBack.box.y - ScrollItem.box.y;
			}
			else if (mouse_y_motion > 0)
			{
				mouse_y_motion = ScrollBack.box.y + ScrollBack.box.h - (ScrollItem.box.h + ScrollItem.box.y);
			}
		}
		if (Scroll_Type == VERTICAL)
		{
			if (MouseIsIn(&App->gui->viewport_box));
			{
				ScrollItem.MoveBox(0, mouse_y_motion);
				p2List_item<Ui_Element*>*  item = Items.start;

				while (item)
				{
					item->data->HandleInput();
					item->data->MoveBox(0, -mouse_y_motion); //Not yet, i think
					item = item->next;
				}
			}

		}
		else if (Scroll_Type == VERTICAL_INV)
		{
			ScrollItem.MoveBox(0, -mouse_y_motion);
			p2List_item<Ui_Element*>*  item = Items.start;

			while (item)
			{
				item->data->HandleInput();
				item->data->MoveBox(0, mouse_y_motion); //Not yet, i think
				item = item->next;
			}
		}
		else if (Scroll_Type == LATERAL)
		{
			ScrollItem.MoveBox(mouse_x_motion, 0);
			p2List_item<Ui_Element*>*  item = Items.start;

			while (item)
			{
				item->data->HandleInput();
				item->data->MoveBox(mouse_x_motion, 0); //Not yet, i think
				item = item->next;
			}
		}
		else if (Scroll_Type == LATERAL_INV)
		{
			ScrollItem.MoveBox(-mouse_x_motion, 0);
			p2List_item<Ui_Element*>*  item = Items.start;

			while (item)
			{
				item->data->HandleInput();
				item->data->MoveBox(-mouse_x_motion, 0); //Not yet, i think
				item = item->next;
			}
		}


	}

	return ScrollSelected;
}

void UI_Scroll::AddScrollItem(Ui_Element* new_item, uint sumlayer)
{

	//Calculate the size for the scroll
	int lenght = 0;
	if(Scroll_Type == VERTICAL || Scroll_Type == VERTICAL_INV)
	{
		//Vertical Scroll Case
		lenght = new_item->box.y - (itemsWindow.h - itemsWindow.y) + new_item->box.h;
		if (lenght > 0 && lenght > ContentLenght)
		{
			ContentLenght = lenght;
		}
	}
		//Lateral Scroll Case
	else
	{
		lenght = new_item->box.x - (itemsWindow.w - itemsWindow.x) + new_item->box.w;
		if (lenght > 0 && lenght > ContentLenght)
		{
			ContentLenght = lenght;
		}

	}
	if (new_item->ui_type == BUTTON)
	{
		new_item->SetParent(this);
		this->childs.add(new_item);
	}
	if (new_item->ui_type == TEXT_BOX)
	{
		new_item->SetParent(this);
		this->childs.add(new_item);
	}
	//Set item layer
	new_item->layer = this->layer + sumlayer;

	//Add the new item to the list of items
	this->Items.add(new_item);
}


