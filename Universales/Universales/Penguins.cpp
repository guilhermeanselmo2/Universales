#include "Penguins.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"

Penguins *Penguins::player;
Timer tShoot;

Penguins::Penguins(float x, float y) {
	
	bodySp.Open("img/penguindad.png");
	cannonSp.Open("img/cubngun.png");
	box.SetRect((x - (bodySp.GetWidth() / 2)), (y - (bodySp.GetHeight() / 2)), (float)bodySp.GetWidth(), (float)bodySp.GetHeight());
	rotation = 0;
	hp = 30;
	linearSpeed = 0;
	speed.SetXpoint(1);
	speed.SetYpoint(1);
	cannonAngle = 0;
	player = this;
}

Penguins::~Penguins() {
	player = NULL;
}

void Penguins::Update(float dt) {
	tShoot.Update(dt);
	float limSpeedpos = 190, limSpeedneg = -190;
	if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
		if (linearSpeed > limSpeedneg)
			linearSpeed -= dt*100;
		}
	if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
		if (linearSpeed < limSpeedpos)
			linearSpeed += dt*100;
		}
	if (!(InputManager::GetInstance().IsKeyDown(SDLK_w) || InputManager::GetInstance().IsKeyDown(SDLK_s))){
		linearSpeed -= dt*linearSpeed;
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_a)){
		rotation -= dt*100;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
		rotation += dt*100;
	}
	if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
		if (tShoot.Get() > 0.4) {
			Shoot();
			tShoot.Restart();
		}
	}		
	if ((linearSpeed < 1) && (linearSpeed > -1))
		box.SetRect(box.GetXrect(), box.GetYrect(), box.GetWrect(), box.GetHrect());
	else
		box.SetRect(box.GetXrect() - dt*linearSpeed*cos((rotation*M_PI) / 180), box.GetYrect() - dt*linearSpeed*sin((rotation*M_PI) / 180), box.GetWrect(), box.GetHrect());
	cannonAngle = box.CenterRect(box).Inclinacao(InputManager::GetInstance().GetMouseX() - Camera::pos.GetXpoint(), InputManager::GetInstance().GetMouseY() - Camera::pos.GetYpoint(), box.CenterRect(box));
	

}

void Penguins::Render(int cameraX, int cameraY) {
	bodySp.Render(((int)box.GetXrect() + cameraX), ((int)box.GetYrect() + cameraY), rotation);
	cannonSp.Render ((int)(box.GetXrect() - (cannonSp.GetWidth() - bodySp.GetWidth())/2) + cameraX, (int)(box.GetYrect() - (cannonSp.GetHeight() - bodySp.GetHeight())/2) + cameraY,((cannonAngle * 180) / M_PI));
}

void Penguins::NotifyCollision(GameObject& other) {

}

bool Penguins::IsDead() {
	if (hp <= 0) {
		player = NULL;
		return true;
	}
	return false;
}

void Penguins::Shoot() {

}

bool Penguins::Is(string type) {
	if (type == "Penguins")
		return true;
	return false;
}

void Penguins::AddObjective(float x, float y){
}