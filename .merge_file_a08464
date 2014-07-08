#include "PauseState.h"


PauseState::PauseState() :bg("img/fundo_espaco.png"),
	text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "Cultura Univer$ale", WHITE, 100),
	resumeButton("resume", 30, 256, 300),
	optionsButton("options", 30, 256, 370),
	quitButton("quit", 30, 256, 440){
	text.SetPos(512, 60, true, true);
}


PauseState::~PauseState()
{
}

void PauseState::Update(float dt){
	Input();
	resumeButton.Update(dt);
	optionsButton.Update(dt);
	quitButton.Update(dt);
}

void PauseState::Render(){
	bg.Render(0, 0);
	//StageState::instance->Render();
	text.Render();
	resumeButton.Render();
	optionsButton.Render();
	quitButton.Render();
}

void PauseState::Input(){

	requestQuit = InputManager::GetInstance().ShouldQuit();

	if (quitButton.pressed){
		requestQuit = true;
	}
	if (resumeButton.pressed){
		requestDelete = true;
	}
}
