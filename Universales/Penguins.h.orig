#ifndef PenguinsH
#define PenguinsH

#include "GameObject.h"
#include "Sprite.h"

class Penguins : public GameObject {
private:
	Sprite bodySp;
	Sprite cannonSp;
	Point speed;
	float linearSpeed;
	float cannonAngle;
	int hp;

public:
	static Penguins* player;
	Penguins(float x, float y);
	~Penguins();
	void Update(float df);
	void Render(int cameraX, int cameraY);
	bool IsDead();
	void Shoot();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	void AddObjective(float x, float y);

};

#endif