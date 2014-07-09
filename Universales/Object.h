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
	Object(ifstream &file, TileMap tileMap);
	~Object();

	void Update(float dt, vector<unique_ptr<GameObject>> *objectArray);
	void Render(int cameraX, int cameraY);

	void MoveTo(int x, int y);
	bool SettlePos(vector<int> obstacleMap);
	void SetFrameCount(int frameCount);
	void SetFrame(int frame);
	void SetCurrentHeight(int currentHeight);
	bool IsDead();
	bool Is(string type);
	void Editing(bool editing);
	void AddObjective(float x, float y, Point tile);
	void AddObjective(vector<int> path);
	bool IsCharacter();
	string Type();
	string GetChoice();
	vector<string>GetTextAttributes();

	vector<int> GetAttributes();
	vector<Point> GetAccessPoints();

	vector<int> CreateHeuristic(Point door);
	vector<int> GetHeuristic(int i);

	Rect GetBox();
	Point GetTile();

	int MakeDeposit();

	//Char functions
	int GetHunger();
	void Save(ofstream &file);
	void SetHunger(int hunger);
	ActionCharacter GetAction();
	int GetObjectIndex();
	void UseObject(vector<unique_ptr<GameObject>> *objectArray, int index);
	void ChangeSelection(int reference);
	void CancelGoal();

	Sprite sp;
	Rect box;

private:
	vector<vector<int>> heuristicArray;
	vector<Point> accessPoints;
	Attributes attributes;
	TileMap tileMap;
	Timer timer;
	string type;
	int deposit;

};

