#ifndef GameObjectH
#define GameObjectH

#include "Rect.h"
#include <string>
#include <vector>

using std::string;
using namespace std;

class GameObject {

public:
	float rotation;
	GameObject();
	virtual void Update(float dt) = 0;
	virtual void Render(int cameraX, int cameraY) = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject& other) = 0;
	virtual bool Is(string type) = 0;
	virtual void Editing(bool editing) = 0;
	//string Type();
	virtual void AddObjective(float x, float y, Point tile) = 0;
	virtual bool IsCharacter() = 0;
	virtual string Type() = 0;
	
	//void ConvertToTile(TileMap *tileMap);
	//void ConvertToScreen(TileMap *tileMap);
	Rect box;
	Point tile;
	int roomID;
};

#endif