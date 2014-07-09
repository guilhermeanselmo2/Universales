#ifndef GameObjectH
#define GameObjectH

#include "Rect.h"
#include <string>

using std::string;

class GameObject {

public:
	float rotation;
	GameObject();
	virtual void Update(float dt) = 0;
	virtual void Render(int cameraX, int cameraY) = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject& other) = 0;
	virtual bool Is(string type) = 0;
	//string Type();
	virtual void AddObjective(float x, float y) = 0;
	Rect box;
	int roomID;
};

#endif