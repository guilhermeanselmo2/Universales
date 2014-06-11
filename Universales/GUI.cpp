#include "GUI.h"
#include "InputManager.h"
#include <algorithm>

GUI::GUI() : buildIcon("img/icons/build.png"), destroyIcon("img/icons/destroy.png"), buyIcon("img/icons/destroy.png"), editIcon("img/icons/editar.jpg"){
    box.w = buildIcon.GetWidth() + destroyIcon.GetWidth() + buyIcon.GetWidth();
    box.h = max(buildIcon.GetHeight(),destroyIcon.GetHeight());

    buildBox.w = buildIcon.GetWidth();
    buildBox.h = buildIcon.GetHeight();

    destroyBox.w = destroyIcon.GetWidth();
    destroyBox.h = destroyIcon.GetHeight();

	buyBox.w = buyIcon.GetWidth();
	buyBox.h = buyIcon.GetHeight();

	editBox.w = editIcon.GetWidth();
	editBox.h = editIcon.GetHeight();
}

GUI::~GUI(){

}

void GUI::Render(){
    buildIcon.Render(buildBox.x, buildBox.y);
    destroyIcon.Render(destroyBox.x, destroyBox.y);
	buyIcon.Render(buyBox.x, buyBox.y);
	editIcon.Render(editBox.x, editBox.y);
}

void GUI::SetPosition(float x, float y){
    box.x = x;
    box.y = y;

    buildBox.x = x;
    buildBox.y = y;

    destroyBox.x = x + buildBox.w;
    destroyBox.y = y;

	buyBox.x = x + destroyBox.w + buildBox.w;
	buyBox.y = y;

	editBox.x = x + buildBox.w + destroyBox.w + buyBox.w;
	editBox.y = y;
}

void GUI::SetPosition(Point p){
    box.x = p.x;
    box.y = p.y;

    buildBox.x = p.x;
    buildBox.y = p.y;

    destroyBox.x = p.x + buildBox.w;
    destroyBox.y = p.y;

	buyBox.x = p.x + destroyBox.w + buildBox.w;
	buyBox.y = p.y;

	editBox.x = p.x + buildBox.w + destroyBox.w + buyBox.w;
	editBox.y = p.y;
}

bool GUI::BuildIconPressed(){
    float x,y;
    x = InputManager::GetInstance().GetMouseX();
    y = InputManager::GetInstance().GetMouseY();
    return buildBox.IsInside(x,y);
}

bool GUI::BuyIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return buyBox.IsInside(x, y);
}

bool GUI::EditIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return editBox.IsInside(x, y);
}

bool GUI::DestroyIconPressed(){
    float x,y;
    x = InputManager::GetInstance().GetMouseX();
    y = InputManager::GetInstance().GetMouseY();
    return destroyBox.IsInside(x,y);
}

bool GUI::IsInside(){
    float x,y;
    x = InputManager::GetInstance().GetMouseX();
    y = InputManager::GetInstance().GetMouseY();
    return box.IsInside(x,y);
}
