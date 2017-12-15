#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2List.h"
#include "j1TimeNormal.h"

struct SDL_Texture;
struct UI_Button;
struct UI_String;
struct Ui_img;
struct Ui_Element;
struct UI_Text_Box;
struct UI_Scroll;

#define PlayerLifes 5

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

	void LoadUi();
	void NewGame();
	void SetLevelInfo(int lvl);

	void SetLife(UI_Button* life, int& number);

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

public:
	Ui_Element*		mainscene = nullptr;
private:
	//SDL_Texture* img;
	bool settingOpen = false;
	bool goOpen = true;

	Ui_img*			imageLVL = nullptr;
	UI_Text_Box*	actualvl = nullptr;
	p2List<UI_Button*> lifes;
	int numlifesactive;
	UI_Button*		buttonReturnMenu = nullptr;
	UI_String*		Options = nullptr;
	UI_Button*		O_imgButtonReturn = nullptr;
	UI_String*		S_imgButtonReturn = nullptr;
	UI_Button*		O_imgLoad = nullptr;
	UI_String*		S_imgLoad = nullptr;
	UI_Button*		O_imgSave = nullptr;
	UI_String*		S_imgSave = nullptr;

	UI_Scroll*		scroll = nullptr;
	Ui_img*			test = nullptr;
	
	char buffer[33];
	j1TimeNormal	playtime;
	Ui_img*			clock = nullptr;
	UI_String*		clocktime = nullptr;

	//2-634-170-87 
};

#endif // __j1SCENE_H__