#ifndef CharacterH
#define CharacterH
#include "Point.h"

enum CharType{
	PERMONKEY = 0,
};

class Character {
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
