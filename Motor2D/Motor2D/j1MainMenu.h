#ifndef __j1MAINMENU_H__
#define __j1MAINMENU_H__

#include "j1Module.h"


struct SDL_Texture;
struct UI_Button;
struct UI_String;
struct Ui_img;
struct Ui_Element;
struct UI_Text_Box;
struct UI_Scroll;

struct SDL_Texture;

class j1MainMenu : public j1Module
{
public:
	j1MainMenu();
	// Destructor
	virtual ~j1MainMenu();

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

private:
	bool isLoadedUI = false;
	bool isNewGame = true;
public: 
	SDL_Texture* background = nullptr;

	//Scene Element
	Ui_Element*		mainscene = nullptr;
	
	//Play Button
	UI_Button*		button = nullptr;
	UI_String*		play_button = nullptr;

	//Exit Button
	UI_Button*		button2 = nullptr;
	UI_String*		Exit_button = nullptr;

	//Continue Button
	UI_Button*		button3 = nullptr;
	UI_String*		Continue_button = nullptr;

	//Settings Button
	UI_Button*		button4 = nullptr;
	UI_String*		settings_button = nullptr;

	//Credits Button
	UI_Button*		button5 = nullptr;
	UI_String*		Credits_button = nullptr;

	//Close Settings Button
	UI_Button*     close_settings_button = nullptr;
	
	//Close Credits Button
	UI_Button*     close_credits_button = nullptr;

	//Settings Window
	Ui_img*		   settings_window = nullptr;

	//Credits Window
	Ui_img*		   credits_window = nullptr;
	UI_Button*     openWeb = nullptr;

};

#endif
