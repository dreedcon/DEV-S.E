#ifndef __UI_SCROLL__
#define __UI_SCROLL__

#include "UI_Element.h"
#include "UI_IMG.h"

enum SCROLL_TYPE {

	VERTICAL,
	LATERAL,
	VERTICAL_INV,
	LATERAL_INV

};

class UI_Scroll : public Ui_Element {
public:

	UI_Scroll(const SDL_Rect& box, const SDL_Rect& ContentWindow, const Ui_img& ScrollItem, const Ui_img& ScrollBack, bool HaveScroll_bar, SCROLL_TYPE Scroll_Type = VERTICAL);
	UI_Scroll(const UI_Scroll* copy);
	UI_Scroll();
	~UI_Scroll();

public:

	//Game Loop
	void	Draw(bool debug)const;
	bool	Update();
	void	HandleInput();


	//Functionality
	bool		MoveScroll(int mouse_y_motion, int mouse_x_motion);
	void		AddScrollItem(Ui_Element* new_item, uint sumlayer);

private:

	SDL_Rect				itemsWindow;
	SCROLL_TYPE				Scroll_Type;
	uint					ContentLenght = 0;
	p2List<Ui_Element*>		Items;
	Ui_img					ScrollItem;
	Ui_img					ScrollBack;
	bool					ScrollSelected;
	bool					haveScroll_bar;

};
#endif