#pragma once

#include "State.h"
#include "Text.h"
#include "Button.h"
#include "Sprite.h"

class PauseState : public State
{
public:
	PauseState();
	~PauseState();
	void Update(float dt);
	void Render();

private:
	void Input();

	Text text;
	Button resumeButton;
	Button optionsButton;
	Button quitButton;
	Sprite bg;
};

