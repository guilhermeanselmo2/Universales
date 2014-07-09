#pragma once
#include "State.h"
#include "Text.h"
#include "InputManager.h"
#include "SDL.h"
#include "Rect.h"
#include "StateData.h"
class CheatState :
	public State
{
public:
	CheatState(State *state, StateData *data);
	~CheatState();
	void Update(float dt);
	void Render();
private:
	void Input();
	void ChechCheat();
	State *state;
	SDL_Texture *texture;
	Rect box;
	string msg;
	Text text;
	StateData *data;
};

