#ifndef TitleStateH
#define TitleStateH

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State {

private:
	void Input();
	Sprite bg;
	SDL_Color cor;
	Text texto1;
public:
	TitleState();
	void Update(float dt);
	void Render();
};

#endif