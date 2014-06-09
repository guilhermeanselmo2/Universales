#include "StillAnimation.h"

StillAnimation::StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends) : sp(sprite), oneTimeOnly(ends), timeLimit(timeLimit) {
	box.SetRect((x - (sp.GetWidth() / 2)), (y - (sp.GetHeight() / 2)), (float)sp.GetWidth(), (float)sp.GetHeight());
	rotation = 0;
}

void StillAnimation::Update(float dt) {
	endTimer.Update(dt);
}

void StillAnimation::Render(int cameraX, int cameraY) {
	sp.Render(((int)box.GetXrect() + cameraX), ((int)box.GetYrect() + cameraY));
}

bool StillAnimation::IsDead() {
	if (endTimer.Get() >= timeLimit)
		return true;
	return false;
}

void StillAnimation::NotifyCollision(GameObject& other) {}

bool StillAnimation::Is(string type) {
	if (type == "StillAnimation")
		return true;
	return  false;
}

void StillAnimation::AddObjective(float x, float y){
}