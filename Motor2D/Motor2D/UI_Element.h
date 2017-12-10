#ifndef __Ui_Element__
#define __Ui_Element__

#include "p2Point.h"
#include "p2Defs.h"
#include "p2List.h"
#include "j1Gui.h"
#include "SDL\include\SDL_rect.h"

enum UI_TYPE {

	UNDEFINED,
	BUTTON,
	TEXT_BOX,
	STRING,
	IMG,
	SCROLL
};



class Ui_Element {
public:

	Ui_Element(const SDL_Rect& box, UI_TYPE ui_type = UNDEFINED, bool IsActive = true);
	Ui_Element(const Ui_Element* copy);
	Ui_Element();

	~Ui_Element();

public:

	SDL_Rect				box;
	uint					layer = 0;
	mutable bool			IsActive;
	enum UI_TYPE			ui_type;

	Ui_Element*				parent;
	p2List<Ui_Element*>		childs;


private:
	uint					number_tab = 0;

public:

	//App Loop
	virtual bool	Update();
	bool			UpdateChilds();
	virtual bool	CleanUp();
	bool			CleanUpChilds();
	virtual void	Draw(bool debug)const;
	virtual void	DrawAt(int x, int y)const;
	void			DrawChilds(bool debug)const;

	//Detector Mouse
	bool			MouseIsIn()const;
	bool			MouseIsIn(int x, int y)const;
	bool			MouseIsIn(const SDL_Rect* box_rect)const;
	
	//Box
	virtual void	MoveBox(int x_vel, int y_vel);
	void			ResizeBox(const iPoint& new_size);
	void			SetBox(SDL_Rect newbox);
	
	//:D
	bool			RectIsIn(const SDL_Rect* box_rect, int x_vel, int y_vel, bool x_axis = false)const;
	bool			Drag();
	bool			GetActiveState() const;
	void			Activate();
	void			Desactivate();
	bool			Select();
	virtual void	HandleInput();

	//Childs
	void			AddChild(Ui_Element* child, uint start_layer = 0);
	bool			Delete_Child(Ui_Element* child);
	bool			Delete_Child(uint index);
	Ui_Element*		SetParent(const Ui_Element* parent);

	//Tab
	void			SetNumerTab(uint num);
	Ui_Element*		GetelementofTAB();



};

#endif // __Ui_Element__
