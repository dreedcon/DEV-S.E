#ifndef __UI_STRING__
#define __UI_STRING__

#include "UI_Element.h"
#include "j1App.h"
#include "j1Fonts.h"

struct p2SString;
struct _TTF_Font;
struct SDL_Texture;

class UI_String : public Ui_Element {
public:

	UI_String(const SDL_Rect& box, char* text, _TTF_Font* text_font);
	UI_String(const UI_String* copy);
	UI_String();

	~UI_String();

public:

	void		Draw(bool debug)const;
	char*		GetString()const;
	uint		GetLenght()const;
	void		SetString(char* new_text);
	void		PushString(char* new_text,uint position);
	void		Deleteletter(uint position);
	uint		GetPixelLenght(uint end)const;
	void		DrawAt(int x, int y)const;

	p2SString			text;

private:

	_TTF_Font*			text_font;
	SDL_Texture*		text_texture;

};

#endif