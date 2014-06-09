#include "TitleState.h"
#include "Game.h"
#include "StageState.h"

Timer Ttext;

TitleState::TitleState() : bg("img/title.jpg"), texto1("font/Call me maybe.ttf", 30, Text::TEXT_BLENDED, "Pressione Space para continuar", cor, 0, 0) {
	texto1.SetPos(314,462,true,true);
}

void TitleState::Update(float dt) {
	Ttext.Update(dt);
	Input();
}

void TitleState::Render() {
	bg.Render(0, 0);
	if (Ttext.Get() < 1.5){
		texto1.Render();
	}
	if (Ttext.Get() > 2)
		Ttext.Restart();
}

void TitleState::Input() {
	if ((InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) || (InputManager::GetInstance().ShouldQuit())){
		requestQuit = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		StageState *state = new StageState();
		Game::GetInstance().Push(state);
	}
}