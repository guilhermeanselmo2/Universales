<<<<<<< HEAD
#pragma once
#include "GameObject.h"

class Character: public GameObject{
=======
#ifndef CharacterH
#define CharacterH
#include "Point.h"

class Character {
>>>>>>> 01dec036e1fa8a9ffb8189fe584e78ce18927123
public:
	enum ActionCharacter{
		RESTING = 0,
		MOVING
	};
	Character(void);
	virtual void AddObjective(float x, float y, Point tile) = 0;
	virtual void Update(float dt) = 0;

protected:
	int objectiveX, objectiveY;
};

#endif
