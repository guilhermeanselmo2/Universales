#include "GUI.h"
#include "InputManager.h"
#include <algorithm>

GUI::GUI(){}

GUI::GUI(string file1, string file2, string file3, string file4) : buildIcon(file1), destroyIcon(file2), buyIcon(file3), editIcon(file4){
   
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

GUI::GUI(string file1, string file2) : doorIcon(file1), wallIcon(file2) {

	box.w = doorIcon.GetWidth() + wallIcon.GetWidth();
	box.h = max(doorIcon.GetHeight(), wallIcon.GetHeight());

	doorBox.w = doorIcon.GetWidth();
	doorBox.h = doorIcon.GetHeight();

	wallBox.w = wallIcon.GetWidth();
	wallBox.h = wallIcon.GetHeight();

}

GUI::~GUI(){

}

void GUI::Render(){
    buildIcon.Render(buildBox.x, buildBox.y);
    destroyIcon.Render(destroyBox.x, destroyBox.y);
	buyIcon.Render(buyBox.x, buyBox.y);
	editIcon.Render(editBox.x, editBox.y);
	doorIcon.Render(doorBox.x,doorBox.y);
	wallIcon.Render(wallBox.x, wallBox.y);
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

void GUI::SetPositionSubGUI(float x, float y) {
	box.x = x;
	box.y = y;

	doorBox.x = x;
	doorBox.y = y;

	wallBox.x = x + doorBox.w;
	wallBox.y = y;
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

void GUI::SetPositionSubGUI(Point p) {
	box.x = p.x;
	box.y = p.y;

	doorBox.x = p.x;
	doorBox.y = p.y;

	wallBox.x = p.x + doorBox.w;
	wallBox.y = p.y;
}

bool GUI::BuildIconPressed(){
    float x,y;
    x = InputManager::GetInstance().GetMouseX();
    y = InputManager::GetInstance().GetMouseY();
    return buildBox.IsInside(x,y);
}

bool GUI::DoorIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return doorBox.IsInside(x, y);
}

bool GUI::WallIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return wallBox.IsInside(x, y);
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
