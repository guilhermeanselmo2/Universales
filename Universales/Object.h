#pragma once

#include "Sprite.h"
#include "Rect.h"
#include "GameObject.h"
#include "TileMap.h"

struct Attributes{
	string name;
	int cost;
	string type;
	int activeHunger;
	float activeSatisfaction;
	int activeMoney;
	int radius;
	int passiveHunger;
	float passiveSatisfaction;
	int passiveMoney;
	string sprite;
	string description;
};

class Object : public GameObject{
public:
	Object(int x, int y, Attributes attributes, TileMap tileMap);
	~Object();

	void Update(float dt);
	void Render(int cameraX, int cameraY);

	void MoveTo(int x, int y);
	bool IsDead();
	bool Is(string type);
	void Editing(bool editing);
	void AddObjective(float x, float y, Point tile);
	void AddObjective(vector<int> path);
	bool IsCharacter();
	string Type();
	Choice GetChoice();
	int GetHunger();

	Sprite sp;
	Rect box;

private:
	Attributes attributes;
	TileMap tileMap;
};

