#include "UI_String.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "p2SString.h"

//Contructors
UI_String::UI_String(const SDL_Rect& box, char * text, _TTF_Font * text_font) : Ui_Element(box, STRING), text(text), text_font(text_font), text_texture(App->font->Print(this->text.GetString(), { 255,255,255,255 }, text_font)) {}

UI_String::UI_String(const UI_String* copy) : Ui_Element(copy->box, STRING), text(copy->text), text_font(copy->text_font), text_texture(copy->text_texture) {}

UI_String::UI_String() : Ui_Element({0,0}, STRING), text(nullptr), text_font(nullptr) {}

//Destructor
UI_String::~UI_String()
{

}


// ==========================
void UI_String::Draw(bool debug) const
{
	//This Draw
	App->render->Blit(text_texture, box.x - App->render->camera.x, box.y - App->render->camera.y);
	DrawChilds(debug);
}


// ==========================
char * UI_String::GetString() const
{
	return (char*)text.GetString();
}

uint UI_String::GetLenght() const
{
	return uint(text.Length());
}

void UI_String::SetString(char * new_text)
{
	text.create(new_text);
	text_texture = App->font->Print(text.GetString(), { 255,255,255,255 }, text_font);
}

void UI_String::PushString(char * new_text, uint position)
{
	char* test = text.InsertString(new_text, position);
	text.create(test);
	text_texture = App->font->Print(text.GetString(), { 255,255,255,255 }, text_font);
}

void UI_String::Deleteletter(uint position)
{
	text.DeleteChar(position);
	text_texture = App->font->Print(text.GetString(), { 255,255,255,255 }, text_font);
}

uint UI_String::GetPixelLenght(uint end) const
{
	char* segment = text.StringSegment(0, end);
	int x, y;
	App->font->CalcSize(segment, x, y, text_font);
	return x;
}

void UI_String::DrawAt(int x, int y) const
{
	//This Draw
	App->render->Blit(text_texture, box.x + x - App->render->camera.x, box.y + y - App->render->camera.y);

}

void UI_String::setText_Font(_TTF_Font * textfont)
{
	text_font = textfont;
}

/*bool UI_String::Insert(int position, p2SString new_buffer)
{
	uint len = Length();

	if (position < 0)
		position = 0;
	if (position > len + 1)
		position = len + 1;

	if ((position >= 0) && (position <= len + 1))
	{
		uint new_buffer_len = new_buffer.Length();
		uint need_size = new_buffer_len + len + 1;

		//we have enough memory allocated?
		if (need_size > size)
		{
			char* tmp = str;
			Alloc(need_size);
			strcpy_s(str, size, tmp);
			delete[] tmp;
		}

		//now we have anough memory
		// move our string to the end
		for (int j = len, i = need_size - 1; i >= position; i--)
			str[i] = str[j--];

		// prefix new string
		for (int i = 0; i < new_buffer_len; i++)
			str[position + i] = new_buffer.str[i];
	}
	return true;
}*/


