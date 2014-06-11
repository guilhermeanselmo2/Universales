#pragma once
class Character
{
public:
	Character(void);
	virtual void AddObjective(float x, float y) = 0;

protected:
	int objectiveX, objectiveY;
};

