#include "EndState.h"
#include "StageState.h"
#include "TitleState.h"

EndState::EndState(StateData stateData) : instruction("font/Call me maybe.ttf", 30, Text::TEXT_BLENDED, "Pressione Space para tentar novamente ou ESC para ir ao MENU", cor, 0, 0) {
	instruction.SetPos(100, 462, true, true);

	if (stateData.playerVictory == true) {
		bg.Open("img/win.jpg");
		music.Open("audio/endStateWin.ogg");
		music.Play(-1);
	}
	else {
		bg.Open("img/lose.jpg");
		music.Open("audio/endStateLose.ogg");
		music.Play(-1);
	}
}

void EndState::Input() {
	if ((InputManager::GetInstance().ShouldQuit())){
		requestQuit = true;
	}

	if ((InputManager::GetInstance().KeyPress(SDLK_ESCAPE))){
		requestDelete = true;
		music.Stop();
		TitleState *state = new TitleState();
		Game::GetInstance().Push(state);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		StageState *state = new StageState();
		Game::GetInstance().Push(state);
	}
}

void EndState::Update(float dt) {
	Input();
}

void EndState::Render() {
	bg.Render(0, 0);
	instruction.Render();
}