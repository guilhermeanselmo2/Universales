#include "Minion.h"
#include "Bullet.h"
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

	if (center->IsDead()) {
		Sprite animationSp("img/miniondeath.png", 4, 0.08);
		StillAnimation* animation = new StillAnimation(box.CenterRect(box).GetXpoint(), box.CenterRect(box).GetYpoint(), rotation, animationSp, 0.5, true);
		Game::GetInstance().GetCurrentState().AddObject(animation);
	}
}

void Minion::Render(int cameraX,int cameraY) {
	sp.Render(((int)box.GetXrect() + cameraX), ((int)box.GetYrect() + cameraY),rotation);
}

void Minion::Shoot(float x, float y){
	float angulo;
	angulo = box.CenterRect(box).Inclinacao(x,y,box.CenterRect(box));
	Sprite bulletSp("img/minionbullet.png",3,0.08);
	Bullet* bullet = new Bullet(box.CenterRect(box).GetXpoint(),box.CenterRect(box).GetYpoint(),angulo,200.0,800.0,bulletSp,false);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
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

void Minion::AddObjective(float x, float y){
}