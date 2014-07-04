#ifndef GameObjectH
#define GameObjectH

#include "Rect.h"
#include "Character.h"
#include <string>
#include <vector>
#include <memory>

using std::string;
using namespace std;

enum Choice{
	NO_CHOICE = 0,
	PIRATE_C,
	SAMURAI_C,
	CORRIDOR_C,
	GOING_P,
	GOING_S,
};

class GameObject {

public:
	float rotation;
	GameObject();
	virtual void Update(float dt, vector<unique_ptr<GameObject>> *objectArray) = 0;
	virtual void Render(int cameraX, int cameraY) = 0;
	virtual bool IsDead() = 0;
	virtual bool Is(string type) = 0;
	virtual void Editing(bool editing) = 0;

	//For Character
	virtual void AddObjective(float x, float y, Point tile) = 0;
	virtual void AddObjective(vector<int> path) = 0;
	virtual bool IsCharacter() = 0;
	virtual string Type() = 0;
	virtual Choice GetChoice() = 0;
	virtual ActionCharacter GetAction() = 0;
	virtual int GetObjectIndex() = 0;
	virtual void UseObject(vector<unique_ptr<GameObject>> *objectArray, int index) = 0;

	//For object only
	virtual bool SettlePos(vector<int> obstacleMap) = 0;

	//Only way to make it work
	virtual int GetHunger() = 0;
	virtual void SetHunger(int hunger) = 0;
	virtual vector<int> GetHeuristic(int i) = 0;

	virtual void MoveTo(int x, int y) = 0;

	virtual vector<int> GetAttributes() = 0;
	
	//void ConvertToTile(TileMap *tileMap);
	//void ConvertToScreen(TileMap *tileMap);
	Rect box;
	Point tile;
	int roomID;
	float hunger;
	float satisfaction;
	int money;
};

#endif