#ifndef CharacterH
#define CharacterH
#include "Point.h"

enum CharType{
	PERMONKEY = 0,
};

enum ActionCharacter{
	RESTING = 0,
	MOVING,
	DECIDING_ROOM,
	DECIDING_OBJECT,
	USING_OBJECT,
	EXITING,
};

class Character {
public:
	
	Character(void);
	virtual void AddObjective(float x, float y, Point tile) = 0;
	virtual void Update(float dt) = 0;

protected:
	int objectiveX, objectiveY;
};

#endif
