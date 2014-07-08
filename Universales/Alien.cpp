#include "Alien.h"
#include "Bullet.h"
#include "StillAnimation.h"
#include "Penguins.h"
#include "Sound.h"

int Alien::alienCount = 0;

Alien::Alien(float x, float y, int nMinions) : sp("img/alien.png") {
	hp = 30;
	alienCount++;
	box.SetRect((x - (sp.GetWidth() / 2)), (y - (sp.GetHeight() / 2)), (float)sp.GetWidth(), (float)sp.GetHeight());
	for (int k = 0; k < nMinions; k++) {
		minionArray.emplace_back(Minion(this,(2*M_PI*k) / nMinions));
	}
	rotation = 0;
	alienState = RESTING;
}

void Alien::Update(float dt) {
	float mdistancia, distancia;
	int minionPerto = 0;

	for (auto &pair : minionArray) {
		pair.Update(dt);
	}
	
	if (alienState == RESTING){
		shootCooldown.Update(dt);
		if (shootCooldown.Get() > 1)
			if (Penguins::player != NULL) {
				Point pos;
				pos.SetPoint(Penguins::player->box.GetXrect(), Penguins::player->box.GetYrect());
				taskQueue.emplace(pos);
				alienState = MOVING;
			}
	}

	if (alienState == MOVING) {
		
		
		if (taskQueue.front().DisPoints(box.CenterRect(box), taskQueue.front()) > 5){
			float angle;
			angle = taskQueue.front().Inclinacao(box.CenterRect(box), taskQueue.front());
			box.SetRect(box.GetXrect() - dt*160*cos(angle), box.GetYrect() - (dt*160*sin(angle)), box.GetWrect(), box.GetHrect());
		}
		else {
			taskQueue.pop();
				mdistancia = minionArray[0].box.CenterRect(minionArray[0].box).DisPoints(Penguins::player->box.GetXrect(), Penguins::player->box.GetYrect(), minionArray[0].box.CenterRect(minionArray[0].box));
				for (int i = 1; i < minionArray.size(); i++){
					distancia = minionArray[i].box.CenterRect(minionArray[i].box).DisPoints(Penguins::player->box.GetXrect(), Penguins::player->box.GetYrect(), minionArray[i].box.CenterRect(minionArray[i].box));
					if (distancia < mdistancia) {
						minionPerto = i;
						mdistancia = distancia;
					}
				}
				minionArray[minionPerto].Shoot(Penguins::player->box.GetXrect(), Penguins::player->box.GetYrect());
			shootCooldown.Restart();
			alienState = RESTING;
		}
	}
	

	if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)){}

	if (IsDead()) {
		Sprite animationSp("img/aliendeath.png", 4, 0.08);
		StillAnimation* animation = new StillAnimation(box.CenterRect(box).GetXpoint(), box.CenterRect(box).GetYpoint(), rotation, animationSp, 0.5, true);
		Game::GetInstance().GetCurrentState().AddObject(animation);
		Sound boom("audio/boom.wav");
		boom.Play(1);
		alienCount--;
	}
		

	rotation = rotation - 15*dt;
}

void Alien::Render(int cameraX, int cameraY) {
	sp.Render(((int)box.GetXrect() + cameraX), ((int)box.GetYrect() + cameraY),rotation);
	for (auto &pair : minionArray) {
		pair.Render(cameraX,cameraY);
	}
}
bool Alien::IsDead() {
	if (hp<=0)
		return true;
	return false;
}

Alien::~Alien() {}

void Alien::NotifyCollision(GameObject& other) {
	Bullet& bullet = (Bullet&)other;
	if (bullet.Is("Bullet") && bullet.targetsPlayer == true){
		hp -= 10;
	}
}


bool Alien::Is(string type) {
	if (type == "Alien")
		return true;
	return false;
}

void Alien::AddObjective(float x, float y){
}