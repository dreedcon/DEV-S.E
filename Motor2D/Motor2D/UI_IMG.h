#ifndef __UI_IMG__
#define __UI_IMG__

#include "UI_Element.h"

class Ui_img : public Ui_Element {
public:

	Ui_img(const SDL_Rect& box, const SDL_Rect& texture_rect = { 0,0,0,0 }, int texture_id = -1);
	Ui_img(const Ui_img* copy);
	Ui_img();

	~Ui_img();

public:

	void				Draw(bool debug)const;
	SDL_Rect			AdjustBox();
	void				SetTextureRect(SDL_Rect newRect);
	void				DrawAt(int x, int y)const;

	int					texture_id;

private:

	SDL_Rect	texture_rect;


};

#endif // __Ui_img__