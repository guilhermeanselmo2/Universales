#include "GUI.h"
#include "InputManager.h"
#include <algorithm>

GUI::GUI() : buildIcon("img/icons/iconemartelo.png",2,-1,1), destroyIcon("img/icons/iconedestruicao.png",2,-1,1), buyIcon("img/icons/buy2.png"), editIcon("img/icons/editar.jpg"),
pirateIcon("img/icons/pirate.jpg"), samuraiIcon("img/icons/samurai.jpg"), doorIcon("img/icons/door.png"), wallIcon("img/icons/wall.jpg"),
movewallIcon("img/icons/move.png"), expandwallIcon("img/icons/expand.png") {

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

	pirateBox.w = pirateIcon.GetWidth();
	pirateBox.h = pirateIcon.GetHeight();

	doorBox.w = doorIcon.GetWidth();
	doorBox.h = doorIcon.GetHeight();

	wallBox.w = wallIcon.GetWidth();
	wallBox.h = wallIcon.GetHeight();

	movewallBox.w = movewallIcon.GetWidth();
	movewallBox.h = movewallIcon.GetHeight();

	samuraiBox.w = samuraiIcon.GetWidth();
	samuraiBox.h = samuraiIcon.GetHeight();

	expandwallBox.w = expandwallIcon.GetWidth();
	expandwallBox.h = expandwallIcon.GetHeight();

	guiState = BASIC;
}

GUI::~GUI(){

}

void GUI::Render(){
	cout << "Render" << endl;
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
	case EDIT:
		doorIcon.Render(doorBox.x, doorBox.y);
		wallIcon.Render(wallBox.x, wallBox.y);
		break;
	case EDIT_WALL_GUI:
		cout << "EDIT_WALL_GUI" << endl;
		movewallIcon.Render(movewallBox.x, movewallBox.y);
		expandwallIcon.Render(expandwallBox.x, expandwallBox.y);
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

	doorBox.x = editBox.x;
	doorBox.y = editBox.y + doorBox.h;

	wallBox.x = doorBox.x + wallBox.w;
	wallBox.y = doorBox.y;

	movewallBox.x = wallBox.x;
	movewallBox.y = wallBox.y - movewallBox.h;

	expandwallBox.x = movewallBox.x + expandwallBox.w;
	expandwallBox.y = movewallBox.y;
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

	doorBox.x = p.x;
	doorBox.y = p.y;

	wallBox.x = p.x + doorBox.w;
	wallBox.y = p.y;

	movewallBox.x = wallBox.x;
	movewallBox.y = wallBox.y - movewallBox.h;

	expandwallBox.x = movewallBox.x + expandwallBox.w;
	expandwallBox.y = movewallBox.y;
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

void GUI::SetFrameBuildIcon(int currentFrame) {
	buildIcon.SetFrame(currentFrame);
}

void GUI::SetFrameDestroyIcon(int currentFrame) {
	destroyIcon.SetFrame(currentFrame);
}

bool GUI::DoorIconPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return doorBox.IsInside(x, y);
}

bool GUI::MoveWallPressed(){
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return movewallBox.IsInside(x, y);
}

bool GUI::ExpandwallPressed() {
	float x, y;
	x = InputManager::GetInstance().GetMouseX();
	y = InputManager::GetInstance().GetMouseY();
	return expandwallBox.IsInside(x, y);
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

