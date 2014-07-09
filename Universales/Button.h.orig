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
	void UpdateTxt(string txt);
	void UpdatePos(int x, int y);
	bool pressed;
	void Render();
private:
	Point pt;
	Rect area;
	Text *texto;
	string content;
};

