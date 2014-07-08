#pragma once
#include "State.h"
#include "Button.h"
#include "Sprite.h"
#include "Language.h"
#include "StateData.h"
#include "Sound.h"

class OptionsState : public State {
public:
	OptionsState();
	~OptionsState();
	void Update(float dt);
	void Render();
private:
	void Input();
	int ind1;
	Text text;
	Button resButton;
	Button fsButton;
	Button langButton;
	Button backButton;
	Sprite bg;
	string add1, add2;
	Sound click;
};

