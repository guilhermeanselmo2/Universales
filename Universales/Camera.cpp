#include "Camera.h"

float Camera::speed = 174.0;
Point Camera::pos;
GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = NULL;
}

void Camera::Update(float dt) {

	if (focus != NULL){

		pos.SetXpoint((focus->box.CenterRect(focus->box).GetXpoint()*-1)+512);
		pos.SetYpoint((focus->box.CenterRect(focus->box).GetYpoint()*-1)+300);

	}
	else {
		if (InputManager::GetInstance().IsKeyDown(SDLK_UP) && InputManager::GetInstance().IsKeyDown(SDLK_LEFT)){
			pos.SetYpoint(pos.GetYpoint() + (dt*speed*sqrt(2)/2));
			pos.SetXpoint(pos.GetXpoint() + (dt*speed*sqrt(2)/2));
			return;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_UP) && InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)){
			pos.SetYpoint(pos.GetYpoint() + (dt*speed*sqrt(2) / 2));
			pos.SetXpoint(pos.GetXpoint() - (dt*speed*sqrt(2) / 2));
			return;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN) && InputManager::GetInstance().IsKeyDown(SDLK_LEFT)){
			pos.SetYpoint(pos.GetYpoint() - (dt*speed*sqrt(2) / 2));
			pos.SetXpoint(pos.GetXpoint() + (dt*speed*sqrt(2) / 2));
			return;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN) && InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)){
			pos.SetYpoint(pos.GetYpoint() - (dt*speed*sqrt(2) / 2));
			pos.SetXpoint(pos.GetXpoint() - (dt*speed*sqrt(2) / 2));
			return;
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_UP)){
			pos.SetYpoint(pos.GetYpoint() + (dt*speed));
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN)){
			pos.SetYpoint(pos.GetYpoint() - (dt*speed));
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT)){
			pos.SetXpoint(pos.GetXpoint() + (dt*speed));
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)){
			pos.SetXpoint(pos.GetXpoint() - (dt*speed));
		}
	}
}