#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"

#include "UI_Text_Box.h"

//Constructors ============================================
UI_Text_Box::UI_Text_Box(const SDL_Rect& box, const UI_String& Text_entered, bool IsPassword) :Ui_Element(box, TEXT_BOX), Text_entered(Text_entered), IsPassword(IsPassword) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* copy) : Ui_Element(copy->box, copy->ui_type), Text_entered(copy->Text_entered) , IsPassword(copy->IsPassword) {}

UI_Text_Box::UI_Text_Box() : Ui_Element({0,0,0,0}, TEXT_BOX), IsPassword(false) {}


UI_Text_Box::~UI_Text_Box()
{

}



void UI_Text_Box::Draw(bool debug) const
{
	if (debug)
	{
		App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 25, 25, 25);
	}

	if (App->gui->ItemSelected == this)
	{
		App->render->DrawQuad({ box.x + (int)Cursor_screen_pos, box.y + 0,3,15 }, 120, 50, 200);
	}

	if (Text_entered.GetLenght())
	{
		Text_entered.DrawAt(box.x, box.y);
	}

	DrawChilds(debug);
}

void UI_Text_Box::HandleInput()
{
	/*j1KeyState mouse_key_1 = App->input->GetMouseButtonDown(1);
	if (MouseIsIn() && mouse_key_1 == KEY_DOWN)
	{
		App->gui->ItemSelected = this;
	}*/
	if (App->gui->ItemSelected != this)
	{
		return;
	}
	if (App->gui->type_input == INPUT_TYPE::INPUT_LEFT && Cursor_pos > 0)
	{
		Cursor_pos--;
	}
	else if (App->gui->type_input == INPUT_TYPE::INPUT_RIGHT && Cursor_pos < Text_entered.GetLenght())
	{
		Cursor_pos++;
	}
	else if (App->gui->type_input == INPUT_TYPE::INPUT_BACKSPACE && Cursor_pos > 0)
	{
		Text_entered.Deleteletter(Cursor_pos - 1);
		Cursor_pos--;
	}
	else if (App->gui->type_input == INPUT_TYPE::INPUT_DELETE_INPUT && Cursor_pos < Text_entered.GetLenght())
	{
		Text_entered.Deleteletter(Cursor_pos);
	}


	Cursor_screen_pos = Text_entered.GetPixelLenght(Cursor_pos);
}

char * UI_Text_Box::GetText() const
{
	return Text_entered.GetString();
}

uint UI_Text_Box::GetTextLength() const
{
	return Text_entered.GetLenght();
}

void UI_Text_Box::SetText(char* new_text)
{
	Text_entered.SetString(new_text);
}

void UI_Text_Box::SetCursorPos(uint position)
{
	Cursor_pos = position;
}

uint UI_Text_Box::GetCursorPos() const
{
	return Cursor_pos;
}