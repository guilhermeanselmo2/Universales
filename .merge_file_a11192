#include "Wall.h"
#include "GameObject.h"
#include "Camera.h"

Wall::Wall(float centerX, float centerY, string file, WallStyle lStyle, int lRoom){

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

}

void Wall::Render(int cameraX, int cameraY){
	wall.Render(box.x+Camera::pos.x, box.y+Camera::pos.y);

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


void Wall::AddObjective(float x, float y){
}