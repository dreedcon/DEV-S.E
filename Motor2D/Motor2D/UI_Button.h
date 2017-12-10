#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "UI_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"


enum BUTTON_STATE {

	ON,
	OFF,
	OVER

};

class UI_Button : public Ui_Element {
public:

	UI_Button(const SDL_Rect& box, const Ui_img& tex_on, const Ui_img& tex_off, const Ui_img& tex_over);
	UI_Button(const UI_Button* copy);
	UI_Button();

	~UI_Button();

private:

	Ui_img			tex_on;
	Ui_img			tex_off;
	Ui_img			tex_over;

public:
	BUTTON_STATE	button_state;
	//App Loop
	void	Draw(bool debug)const;
	bool	Update();

	//Functionality
	void			Change_State(BUTTON_STATE new_button_state);
	void			HandleInput();
};

#endif // __UI_BUTTON__