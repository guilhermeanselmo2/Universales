#ifndef AlienH
#define AlienH

#include "GameObject.h"
#include "Sprite.h"
#include "Minion.h"
#include <queue>
#include <vector>
#include "Timer.h"

class Alien : public GameObject {
private:
	Sprite sp;
	Point speed;
	int hp;
	std::queue<Point> taskQueue;
	std::vector<Minion> minionArray;
	enum AlienState { MOVING, RESTING};
	AlienState alienState;
	Timer shootCooldown;
public:
	static int alienCount;
	Alien(float x, float y, int nMinions);
	~Alien();
	void Update(float dt);
	void Render(int cameraX, int cameraY);
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	void AddObjective(float x, float y);
};

#endif