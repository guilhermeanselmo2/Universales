#include "Game.h"
#include "Penguins.h"
#include <stdio.h>
#include <cstring>
#include "Collision.h"
#include "TitleState.h"


Game *Game::instance = NULL;

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

Game& Game::GetInstance() {
	return *instance;
}

State& Game::GetCurrentState() {
	return *(instance->stateStack.top());
}

void Game::Push(State* state) {
	storedState = state;
}

void Game::Run() {
	stateStack.emplace(storedState);
	storedState = NULL;

	while (!stateStack.top()->RequestedQuit()) {
		if (Penguins::player == NULL)
			Camera::Unfollow();
		CalculateDeltaTime();
		if (stateStack.top()->RequestedDelete()) {
			stateStack.pop();
		}
		if (storedState != NULL) {
			stateStack.emplace(storedState);
			storedState = NULL;
		}
		InputManager::GetInstance().Update();
		Camera::Update(dt);
		if (stateStack.empty()){
			cout << "Nenhum estado na fila..." << endl;
			abort();
		}
		stateStack.top()->Update(dt);
		stateStack.top()->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}

void Game::CalculateDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
	dt = dt / 1000;
	frameStart = SDL_GetTicks();
}

Game::Game(string title, int width, int height) {
	storedState = NULL;
	srand(time(NULL));
	frameStart = SDL_GetTicks();
	if (instance == NULL) {
		instance = this;
	}

	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS)) != 0) {
		cout << "Erro ao inicializar SDL..." << SDL_GetError() << endl;
		system("pause");
		exit(1);
	}

	if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)) {
		cout << "Erro ao inicializar IMG..." << SDL_GetError() << endl;
		system("pause");
		exit(1);
	}

	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	TTF_Init();

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if (window == NULL) {
		cout << "Erro ao abrir janela..." << SDL_GetError() << endl;
		system("pause");
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		cout << "Erro ao renderizar..." << SDL_GetError() << endl;
		system("pause");
		exit(1);
	}
	TitleState *state = new TitleState();
	Push(state);
}

float Game::GetDeltaTime() {
	return dt;
}

Game::~Game() {
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	Sprite::Clear();
	TTF_Quit();
}

/*void Game::AddObject(int mouseX, int mouseY) {
	float pX, pY;
	float angulo = (float)(((rand() % 360) * 2 * M_PI) / 360);

	pX = mouseX + 200 * cos(angulo);
	pY = mouseY + 200 * sin(angulo);

	Face* face = new Face(pX, pY);
	objectArray.emplace_back(face);
}*/

