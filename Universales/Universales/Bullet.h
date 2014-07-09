#ifndef BulletH
#define BulletH

#include "GameObject.h"
#include "Sprite.h"

class Bullet : public GameObject {
private:
	Sprite sp;
	Point speed;
	float distanceLeft;

public:
	Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, bool targetsPlayer);
	void Update(float dt);
	void Render(int cameraX, int cameraY);
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	bool targetsPlayer;
	void AddObjective(float x, float y);
};


#endif