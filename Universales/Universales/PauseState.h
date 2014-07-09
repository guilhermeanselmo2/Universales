#pragma once

#include "State.h"
#include "Text.h"
#include "Button.h"
#include "Sprite.h"
#include "Language.h"
#include "OptionsState.h"
#include "StageState.h"
#include "Sound.h"

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
	Button saveButton;
	Button optionsButton;
	Button quitButton;
	Sprite bg;
	Sound click;
};

