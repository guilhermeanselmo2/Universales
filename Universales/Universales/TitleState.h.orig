#ifndef TitleStateH
#define TitleStateH

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Button.h"

class TitleState : public State {

private:
	void Input();
	Sprite bg;
	SDL_Color cor;
	Text text;
	Button startButton;
	Button optionsButton;
	Button quitButton;
public:
	TitleState();
	void Update(float dt);
	void Render();
};

#endif