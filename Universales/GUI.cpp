#include "GUI.h"
#include "InputManager.h"
#include <algorithm>

GUI::GUI() : buildIcon("img/icons/build.png"), destroyIcon("img/icons/destroy.png"), buyIcon("img/icons/buy2.png"), editIcon("img/icons/editar.jpg"), pirateIcon("img/icons/pirate.jpg"), samuraiIcon("img/icons/samurai.jpg"){
    box.w = buildIcon.GetWidth()*4;
    box.h = buildIcon.GetHeight()*2;

    buildBox.w = buildIcon.GetWidth();
    buildBox.h = buildIcon.GetHeight();

    destroyBox.w = destroyIcon.GetWidth();
    destroyBox.h = destroyIcon.GetHeight();

	buyBox.w = buyIcon.GetWidth();
	buyBox.h = buyIcon.GetHeight();

	editBox.w = editIcon.GetWidth();
	editBox.h = editIcon.GetHeight();

	cout << pirateIcon.GetHeight() << endl; 

	pirateBox.w = pirateIcon.GetWidth();
	pirateBox.h = pirateIcon.GetHeight();


	samuraiBox.w = samuraiIcon.GetWidth();
	samuraiBox.h = samuraiIcon.GetHeight();

	guiState = BASIC;
}

GUI::~GUI(){

}

void GUI::Render(){
	switch (guiState){
	case BASIC:
		buildIcon.Render(buildBox.x, buildBox.y);
		destroyIcon.Render(destroyBox.x, destroyBox.y);
		buyIcon.Render(buyBox.x, buyBox.y);
		editIcon.Render(editBox.x, editBox.y);
		break;
	case ROOMS:
		pirateIcon.Render(pirateBox.x, pirateBox.y);
		samuraiIcon.Render(samuraiBox.x, samuraiBox.y);
		break;
	default:
		break;
	}

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

	pirateBox.x = x;
	pirateBox.y = y - pirateBox.h;

	samuraiBox.x = x + pirateBox.w;
	samuraiBox.y = y - destroyBox.h;
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

	pirateBox.x = p.x;
	pirateBox.h = p.y + pirateBox.h;

	samuraiBox.x = p.x + pirateBox.w;
	samuraiBox.h = p.y + destroyBox.h;
}

void GUI::SetState(GuiState newState){
	guiState = newState;
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

bool GUI::PirateIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return pirateBox.IsInside(x, y);
}

bool GUI::SamuraiIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return samuraiBox.IsInside(x, y);
}

bool GUI::IsInside(){
    float x,y;
    x = InputManager::GetInstance().GetMouseX();
    y = InputManager::GetInstance().GetMouseY();
    return box.IsInside(x,y);
}

