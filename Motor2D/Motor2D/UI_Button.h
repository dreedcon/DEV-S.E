#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "UI_Element.h"
#include "UI_IMG.h"
#include "UI_String.h"




class UI_Button : public Ui_Element {
public:

	UI_Button(const SDL_Rect& box, const Ui_img& tex_on, const Ui_img& tex_off, const Ui_img& tex_over);
	UI_Button(const UI_Button* copy);
	UI_Button();

	~UI_Button();

	enum BUTTON_STATE {

		ON,
		OFF,
		OVER

	};
private:

	Ui_img			tex_on;
	Ui_img			tex_off;
	Ui_img			tex_over;
	bool			interactive = true;

public:
	BUTTON_STATE	button_state;
	//App Loop
	void	Draw(bool debug)const;
	bool	Update();

	void			SetInteractive(bool inter_);

	//Functionality
	void			Change_State(BUTTON_STATE new_button_state);
	void			HandleInput();
	void			SetTextures_button(BUTTON_STATE state_texture, Ui_img texture);
};

#endif // __UI_BUTTON__