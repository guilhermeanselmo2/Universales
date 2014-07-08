#include "Minion.h"
#include "StillAnimation.h"

Minion::Minion(GameObject* minionCenter, float angleOffset) : center(minionCenter), angle(angleOffset) {
	float x, y;
	sp.Open("img/minion.png");
	x = center->box.CenterRect(center->box).GetXpoint() + 110*cos(angleOffset);
	y = center->box.CenterRect(center->box).GetYpoint() + 110*sin(angleOffset);
	box.SetRect((x - (sp.GetWidth() / 2)), (y - (sp.GetHeight() / 2)), (float)sp.GetWidth(), (float)sp.GetHeight());
	rotation = 0;
}

void Minion::Update(float dt) {
	float x, y;

	x = center->box.CenterRect(center->box).GetXpoint() +  110 * cos(angle);
	y = center->box.CenterRect(center->box).GetYpoint() +  110 * sin(angle);

	box.SetRect((x - (sp.GetWidth() / 2)), (y - (sp.GetHeight() / 2)), (float)sp.GetWidth(), (float)sp.GetHeight());
	angle = angle + dt;
	rotation = (angle*180)/M_PI +90;

}

void Minion::Render(int cameraX,int cameraY) {
	sp.Render(((int)box.GetXrect() + cameraX), ((int)box.GetYrect() + cameraY),rotation);
}

void Minion::Shoot(float x, float y){

}

bool Minion::IsDead() {
	return false;
}

void Minion::NotifyCollision(GameObject& other) {}

bool Minion::Is(string type){
	if (type == "Minion")
		return true;
	return false;
}

void Minion::Editing(bool editing) {}

void Minion::AddObjective(float x, float y, Point tile){
}