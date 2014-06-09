#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"

TitleState::TitleState() :bg("img/fundo_espaco.png"),
text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "Cultura Univer$ale", WHITE, 100),
startButton("start", 30, 512, 300),
optionsButton("options", 30, 512, 370),
quitButton("quit", 30, 512, 440){
	text.SetPos(512, 60, true, true);

}

void TitleState::Update(float dt){
	Input();
	startButton.Update(dt);
	optionsButton.Update(dt);
	quitButton.Update(dt);
}

void TitleState::Render(){
	bg.Render(0, 0);
	text.Render();
	startButton.Render();
	optionsButton.Render();
	quitButton.Render();
}

void TitleState::Input(){

	requestQuit = InputManager::GetInstance().ShouldQuit();

	if (quitButton.pressed){
		requestQuit = true;
	}
	if (startButton.pressed){
		StageState* s = new StageState();
		Game::GetInstance().Push(s);
		requestDelete = true;
	}
}


