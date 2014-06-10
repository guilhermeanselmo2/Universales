#include "Wall.h"
#include "GameObject.h"
#include "Camera.h"

Wall::Wall(float centerX, float centerY, string file, WallStyle lStyle, int lRoom){
	editing = false;
    roomID = lRoom;
    wall.Open(file);
    switch (lStyle) {
    case UPPER_RIGHT:
        box = Rect(centerX,centerY-wall.GetHeight(), wall.GetWidth(), wall.GetHeight());
        break;
    case UPPER_LEFT:
        box = Rect(centerX,centerY-wall.GetHeight(), wall.GetWidth(), wall.GetHeight());
        break;
    case UPPER_CORNER:
        box = Rect(centerX-wall.GetWidth()/2, centerY-wall.GetHeight(), wall.GetWidth(), wall.GetHeight());
        break;
    case LEFT_CORNER:
        box = Rect(centerX-wall.GetWidth()/2, centerY-wall.GetHeight(), wall.GetWidth(), wall.GetHeight());
        break;
    default:
        break;
    }

}

Wall::~Wall(){

}

void Wall::Update(float dt){
	editTimer.Update(dt);
}

void Wall::Render(int cameraX, int cameraY){
	if (editing){
		if (editTimer.Get() < 2.0){
			wall.Render(box.x + Camera::pos.x, box.y + Camera::pos.y);
		}
		if (editTimer.Get() > 3.0)
			editTimer.Restart();
	}
	else {
		wall.Render(box.x + Camera::pos.x, box.y + Camera::pos.y);
	}
}

bool Wall::IsDead(){
	return false;
}

void Wall::NotifyCollision(GameObject &other){

}

bool Wall::Is(string type){
    return type == "Wall";
}

string Wall::Type(){
    if(style == UPPER_RIGHT || style == UPPER_LEFT|| style == LOWER_RIGHT|| style == LOWER_LEFT)
        return "Wall";
    else
        return "Corner";
}

void Wall::Editing(bool editing) {
	this->editing = editing;
}

void Wall::AddObjective(float x, float y, Point tile){
}