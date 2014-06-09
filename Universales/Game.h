#include "State.h"
#include <stack>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "InputManager.h"
#include "Camera.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::string;
using std::endl;

#ifndef GameH
#define GameH

class Game {

private:
	int frameStart;
	float dt;
	void CalculateDeltaTime();
	static Game *instance;
	State *storedState;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::stack < std::unique_ptr<State>> stateStack;

public:
	static Game& GetInstance();
	static State& GetCurrentState();
	SDL_Renderer* GetRenderer();
	float GetDeltaTime();
	void Push(State* state);
	void Run();
	Game(string title, int width, int height);
	~Game();

};

#endif