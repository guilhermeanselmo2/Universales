#ifndef StillAnimationH
#define StillAnimationH

#include "GameObject.h"
#include "Timer.h"
#include "Sprite.h"

class StillAnimation : public GameObject {
private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;

public:
	StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends);
	void Update(float dt);
	void Render(int cameraX, int cameraY);
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	void AddObjective(float x, float y);
};

#endif