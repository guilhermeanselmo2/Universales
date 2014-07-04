#pragma once

#include "Sprite.h"
#include "Rect.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Timer.h"

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
	int access[4];
	int width;
	int height;
};

class Object : public GameObject{
public:
	Object(int x, int y, Attributes attributes, TileMap tileMap);
	~Object();

	void Update(float dt, vector<unique_ptr<GameObject>> *objectArray);
	void Render(int cameraX, int cameraY);

	void MoveTo(int x, int y);
	bool SettlePos(vector<int> obstacleMap);

	bool IsDead();
	bool Is(string type);
	void Editing(bool editing);
	void AddObjective(float x, float y, Point tile);
	void AddObjective(vector<int> path);
	bool IsCharacter();
	string Type();
	Choice GetChoice();

	vector<int> GetAttributes();

	vector<int> CreateHeuristic(Point door);
	vector<int> GetHeuristic(int i);

	//Char functions
	int GetHunger();
	void SetHunger(int hunger);
	ActionCharacter GetAction();
	int GetObjectIndex();
	void UseObject(vector<unique_ptr<GameObject>> *objectArray, int index);

	Sprite sp;
	Rect box;

private:
	vector<vector<int>> heuristicArray;
	Attributes attributes;
	TileMap tileMap;
	Timer timer;
	string type;
};

