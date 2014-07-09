#ifndef TitleStateH
#define TitleStateH

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Button.h"
#include "OptionsState.h"
#include "Language.h"
#include "Music.h"
#include "Sound.h"

class TitleState : public State {

private:
	void Input();
	Sprite bg;
	SDL_Color cor;
	Text text;
	Sound press;
	Music music;
	Button startButton;
	Button optionsButton;
	Button quitButton;
	Button loadButton;
public:
	TitleState();
	void Update(float dt);
	void Render();
};

#endif