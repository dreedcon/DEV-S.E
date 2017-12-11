#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
struct UI_Button;
struct UI_String;
struct Ui_img;
struct Ui_Element;
struct UI_Text_Box;
struct UI_Scroll;

enum INPUT_TYPE;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void Input_get(INPUT_TYPE type);

	void MoveSelector(INPUT_TYPE type);

private:
	//SDL_Texture* img;

	Ui_Element*		mainscene = nullptr;
	Ui_img*			test = nullptr;
	Ui_img*			test23 = nullptr;
	UI_Text_Box*	text = nullptr;
	UI_Button*		button = nullptr;
	UI_String*		continue_button = nullptr;
	UI_Button*		testbutton = nullptr;
};

#endif // __j1SCENE_H__