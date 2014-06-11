#pragma once
#include "GameObject.h"

class Character: public GameObject{
public:
	Character(void);
	virtual void AddObjective(float x, float y) = 0;

protected:
	int objectiveX, objectiveY;
};

