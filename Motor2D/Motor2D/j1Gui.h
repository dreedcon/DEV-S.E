#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

struct Ui_Element;
struct SDL_Texture;
enum UI_TYPE;

#define CURSOR_WIDTH 2

enum INPUT_TYPE
{
	INPUT_NONDEF,
	INPUT_UP,
	INPUT_DOWN,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_F1,
	INPUT_BACKSPACE,
	INPUT_DELETE_INPUT,
	INPUT_TAB,
	INPUT_CLICK_LEFT
};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	INPUT_TYPE		GetInputType();


private:

	bool debug = false;


	//UI elements
	p2List<Ui_Element*>		screens;

	//UI Textures
	SDL_Texture*			atlas;
	p2List<SDL_Texture*>	ui_textures;
	p2SString				atlas_file_name;



public:

	mutable Ui_Element*			ItemSelected = nullptr;
	mutable uint				upper_element = 0;

	SDL_Rect				viewport_box;
	//UI textures functions
	const SDL_Texture*		GetAtlas() const;
	SDL_Texture*			Get_UI_Texture(uint tex_id);

	//UI elements functions
	uint					PushScreen(const Ui_Element* new_screen);
	uint					CalculateUpperElement(const Ui_Element* parent,uint layer)const;

	Ui_Element*				GenerateUI_Element(UI_TYPE element_type);
	Ui_Element*				GetActiveScreen()const;

	INPUT_TYPE				type_input;
	uint					select_tab = 1;
	p2List<Ui_Element*>		elementCanTab;

};

#endif // __GUI_H__