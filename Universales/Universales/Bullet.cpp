#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, bool targetsplayer) : sp(sprite), distanceLeft(maxDistance), targetsPlayer(targetsplayer) {
	box.SetRect((x - (sp.GetWidth() / 2)), (y - (sp.GetHeight() / 2)), (float)sp.GetWidth(), (float)sp.GetHeight());
	Bullet::speed.SetXpoint(speed*cos(angle));
	Bullet::speed.SetYpoint(speed*sin(angle));
	rotation = (angle*180)/M_PI;
}

void Bullet::Update(float dt) {
	float x, y;
	
	x = box.CenterRect(box).GetXpoint() + dt*speed.GetXpoint();
	y = box.CenterRect(box).GetYpoint() + dt*speed.GetYpoint();

	box.SetRect((x - (sp.GetWidth() / 2)), (y - (sp.GetHeight() / 2)), (float)sp.GetWidth(), (float)sp.GetHeight());
	distanceLeft = distanceLeft - sqrt(((dt*speed.GetXpoint())*(dt*speed.GetXpoint())) + ((dt*speed.GetYpoint())*(dt*speed.GetYpoint())));
}

void Bullet::Render(int cameraX, int cameraY){
	sp.Render(((int)box.GetXrect() + cameraX), ((int)box.GetYrect() + cameraY),rotation);
}

bool Bullet::IsDead() {
	if (distanceLeft <= 0)
		return true;
	return false;
}

void Bullet::NotifyCollision(GameObject& other) {
	if (other.Is("Alien") && targetsPlayer == true)
		distanceLeft = 0;
	if (other.Is("Penguins") && targetsPlayer == false)
		distanceLeft = 0;
}

bool Bullet::Is(string type) {
	if (type == "Bullet")
		return true;
	return  false;
}

void Bullet::AddObjective(float x, float y){
}