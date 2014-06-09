#ifndef EndStateH
#define EndStateH

#include "State.h"
#include "StateData.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"

class EndState : public State {
public:
	SDL_Color cor;
	EndState(StateData stateData);
	void Update(float dt);
	void Render();

private:
	void Input();
	Sprite bg;
	Music music;
	Text instruction;
};

#endif