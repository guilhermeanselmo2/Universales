#pragma once

#include "Sprite.h"
#include "Rect.h"

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

class Object{
public:
	Object();
	~Object();
	int cost;
	Sprite sp;
	Rect box;

private:
	void Parse(vector<string> objList);
	Attributes atributes;
};

