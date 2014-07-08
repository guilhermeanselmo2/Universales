#ifndef MinionH
#define MinionH

#include "GameObject.h"
#include "Sprite.h"
#include "Camera.h"

class Minion : public GameObject {
private:
	GameObject* center;
	Sprite sp;
	float angle;
public:
	Minion(GameObject* minionCenter, float angleOffset = 0);
	void Update(float dt);
	void Render(int cameraX, int cameraY);
	bool IsDead();
	void Shoot(float x, float y);
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	void AddObjective(float x, float y);
};

#endif