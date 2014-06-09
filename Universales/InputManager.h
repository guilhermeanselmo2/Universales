#ifndef InputManagerH
#define InputManagerH

#include <unordered_map>
#include <SDL.h>
#include "Rect.h"

#define N_MOUSE_BUTTONS 5
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE


class InputManager {

private:
	enum InputState{
		RELEASED = 0,
		JUST_RELEASED,
		PRESSED,
		JUST_PRESSED,
	};
	InputManager();
	~InputManager();

	InputState mouseState[N_MOUSE_BUTTONS];
	std::unordered_map<int, InputState> keyState;
	bool quitGame;
	int mouseX;
	int mouseY;

public:
	static InputManager& GetInstance();
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	bool IsMouseInside(Rect rect);
	bool ShouldQuit();
};

#endif