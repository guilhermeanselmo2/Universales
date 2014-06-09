#include "InputManager.h"

InputManager::InputManager() {
	for (int i = 0; i < N_MOUSE_BUTTONS; i++){
		mouseState[i] = RELEASED;
	}
}

InputManager::~InputManager() {}

InputManager& InputManager::GetInstance() {
	static InputManager instance;
	return instance;
}

void InputManager::Update() {
	SDL_Event event;
	quitGame = false;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (int i = 0; i < N_MOUSE_BUTTONS; i++){
		if (mouseState[i] == JUST_RELEASED)
			mouseState[i] = RELEASED;
		if (mouseState[i] == JUST_PRESSED)
			mouseState[i] = PRESSED;
	}

	for (auto &pair : keyState) {
		if (pair.second == JUST_RELEASED)
			pair.second = RELEASED;
		if (pair.second == JUST_PRESSED)
			pair.second = PRESSED;
	}

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN :
			if (keyState[event.key.keysym.sym] == PRESSED)
				break;
			keyState[event.key.keysym.sym] = JUST_PRESSED;
			break;
		case SDL_KEYUP:
			keyState[event.key.keysym.sym] = JUST_RELEASED;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mouseState[event.button.button] == PRESSED)
				break;
			mouseState[event.button.button] = JUST_PRESSED;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseState[event.button.button] = JUST_RELEASED;
			break;
		case SDL_QUIT:
			quitGame = true;
			break;
		}
	}
}

bool InputManager::KeyPress(int key) {
	std::unordered_map< int, InputState >::const_iterator got = keyState.find(key);
	if (got->second == JUST_PRESSED)
		return true;
	return false;
}

bool InputManager::KeyRelease(int key) {
	std::unordered_map< int, InputState >::const_iterator got = keyState.find(key);
	if (got->second == JUST_RELEASED)
		return true;
	return false;
}

bool InputManager::MousePress(int button) {
	if (mouseState[button] == JUST_PRESSED)
		return true;
	return false;
}

bool InputManager::MouseRelease(int button) {
	if (mouseState[button] == JUST_RELEASED)
		return true;
	return false;
}

bool InputManager::IsKeyDown(int key){
	std::unordered_map< int, InputState >::const_iterator got = keyState.find(key);
	if (got->second == PRESSED)
		return true;
	return false;
}

bool InputManager::IsMouseDown(int button) {
	if (mouseState[button] == PRESSED)
		return true;
	return false;
}

bool InputManager::IsMouseInside(Rect rect) {
	if ((rect.GetXrect()<mouseX) && (mouseX<(rect.GetXrect() + rect.GetWrect())) && (mouseY>rect.GetYrect()) && (mouseY<(rect.GetYrect() + rect.GetHrect())))
		return true;
	return false;
}

bool InputManager::ShouldQuit() {
	return quitGame;
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}