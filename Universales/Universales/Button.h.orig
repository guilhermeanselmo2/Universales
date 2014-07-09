#pragma once

#include "Text.h"
#include "Rect.h"
#include "InputManager.h"

class Button
{
public:
	Button(string text, int size, int x, int y);
	~Button();
	void Update(float dt);
	bool pressed;
	void Render();
private:
	Rect area;
	Text *texto;
	string content;
};

