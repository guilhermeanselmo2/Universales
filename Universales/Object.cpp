#include "Object.h"


Object::Object(int x, int y, Attributes attributes): sp(""){
	this->attributes = attributes;
	sp.Open(attributes.sprite);
	box = Rect(x - sp.GetWidth() / 2, y - 3*sp.GetHeight()/4, sp.GetWidth(), sp.GetHeight());

}



Object::~Object(){
}


void Object::Render(int cameraX, int cameraY){
	sp.Render(box.x + Camera::pos.x, box.y + Camera::pos.y);
}

void Object::Update(float dt){

}

void Object::MoveTo(int x, int y){
	box = Rect(x - sp.GetWidth() / 2, y - 3 * sp.GetHeight() / 4, sp.GetWidth(), sp.GetHeight());
}

bool Object::IsDead(){
	return false;
}

bool Object::Is(string type){
	return type == "object";
}


void Object::Editing(bool editing){

}
void Object::AddObjective(float x, float y, Point tile){

}
void Object::AddObjective(vector<int> path){

}

bool Object::IsCharacter(){
	return false;
}

string Object::Type(){
	return "Object";
}

Choice Object::GetChoice(){
	return DECIDING;
}

int Object::GetHunger(){
	return 0;
}
