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
	int volume = 128;
	bool audioActive = true;
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

	//Up Volume
	UI_String*     up_volume_word = nullptr;

	//Down Volume
	UI_String*     down_volume_word = nullptr;

	//Master Volume
	UI_String*     master_volume_word = nullptr;


	//Up Volume
	UI_Button*     up_volume = nullptr;

	//Down Volume
	UI_Button*     down_volume = nullptr;

	//Master Volume
	UI_Button*     master_volume = nullptr;

	//Close Credits Button
	UI_Button*     close_credits_button = nullptr;

	//Settings Window
	Ui_img*		   settings_window = nullptr;

	//Credits Window
	Ui_img*		   credits_window = nullptr;
	
	//Elliot Button go to web
	UI_Button*     elliot_button = nullptr;
	UI_String*	   elliot_jimenez = nullptr;

	//Sergio Button go to web
	UI_Button*     sergio_button = nullptr;
	UI_String*	   sergio_saez = nullptr;

	//Credits string
	UI_String*	   credits = nullptr;

	//License string
	UI_String*	   Lincense = nullptr;
	UI_String*	   Lincense2 = nullptr;
	UI_String*	   Lincense3 = nullptr;


	
	//GitHub Button
	UI_Button*      github_button = nullptr;
};

#endif
