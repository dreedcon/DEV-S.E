#include "UI_IMG.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

//Constructors
Ui_img::Ui_img(const SDL_Rect& box, const SDL_Rect& texture_rect, int texture_id) : Ui_Element(box, IMG), texture_rect(texture_rect), texture_id(texture_id) {}

Ui_img::Ui_img(const Ui_img* copy) : Ui_Element(copy->box, IMG), texture_rect(copy->texture_rect), texture_id(copy->texture_id) {}

Ui_img::Ui_img() : Ui_Element({ 0,0,0,0 }, IMG), texture_rect({ 0,0,0,0 }), texture_id(-1){}

//Destructors
Ui_img::~Ui_img()
{

}


// ==========================
void Ui_img::Draw(bool debug)const
{
	//This Draw
	if (debug)
	{
		App->render->DrawQuad({ box.x, box.y, box.w, box.h }, 150, 50, 0);
	}
	if (texture_id == -1)
	{
		App->render->Blit(((SDL_Texture*)App->gui->GetAtlas()), box.x - App->render->camera.x, box.y - App->render->camera.y, &texture_rect);
	}
	else 
	{

		if (texture_rect.w == 0 || texture_rect.h == 0)
		{
			App->render->Blit(App->gui->Get_UI_Texture(texture_id), box.x - App->render->camera.x, box.y - App->render->camera.y);
		}
		else
		{
			App->render->Blit(App->gui->Get_UI_Texture(texture_id), box.x - App->render->camera.x, box.y - App->render->camera.y, &texture_rect);
		}
	}

	//Childs Draw
	DrawChilds(debug);
}

SDL_Rect Ui_img::AdjustBox()
{

	box.w = texture_rect.w;
	box.h = texture_rect.h;

	if (box.w == 0 || box.h == 0) {

		int w, h;
		SDL_QueryTexture(App->gui->Get_UI_Texture(this->texture_id), NULL, NULL, &w, &h);

		box.w = w;
		box.h = h;
	}

	return box;
}

void Ui_img::SetTextureRect(SDL_Rect newRect)
{
	texture_rect = newRect;
}

void Ui_img::DrawAt(int x, int y) const
{
	x += this->box.x;
	y += this->box.y;

	if (texture_id == -1)
	{
		App->render->Blit(((SDL_Texture*)App->gui->GetAtlas()), x - App->render->camera.x, y - App->render->camera.y, &texture_rect);
	}
	else 
	{
		if (texture_rect.w == 0 || texture_rect.h == 0)
		{
			App->render->Blit(App->gui->Get_UI_Texture(texture_id), x - App->render->camera.x, y - App->render->camera.y);
		}
		else
		{
			App->render->Blit(App->gui->Get_UI_Texture(texture_id), x - App->render->camera.x, y - App->render->camera.y, &texture_rect);
		}
	}
}