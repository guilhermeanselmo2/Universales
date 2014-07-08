#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"

TitleState::TitleState() :bg("img/fundo_espaco.png"),
text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "Cultura Univer$ales", WHITE, 100),
startButton(Language::base[0].c_str(), 30, StateData::resolution[StateData::resInd].x/2, 280),
optionsButton(Language::base[1].c_str(), 30, StateData::resolution[StateData::resInd].x / 2, 350),
loadButton(Language::base[2].c_str(), 30, StateData::resolution[StateData::resInd].x / 2, 420),
quitButton(Language::base[3].c_str(), 30, StateData::resolution[StateData::resInd].x / 2, 490),
music("music/tela_inicial.ogg"),
press("music/click_interface.wav"){
	text.SetPos(StateData::resolution[StateData::resInd].x / 2, 60, true, true);
	music.Play(-1);
}

void TitleState::Update(float dt){
	Input();
	int x = StateData::resolution[StateData::resInd].x / 2;
	text.SetPos(x, 60, true, true);

	startButton.UpdateTxt(Language::base[0].c_str());
	startButton.UpdatePos(x, 280);
	startButton.Update(dt);

	optionsButton.UpdateTxt(Language::base[1].c_str());
	optionsButton.UpdatePos(x,350);
	optionsButton.Update(dt);

	quitButton.UpdateTxt(Language::base[3].c_str());
	quitButton.UpdatePos(x, 490);
	quitButton.Update(dt);

	loadButton.UpdateTxt(Language::base[2].c_str());
	loadButton.UpdatePos(x, 420);
	loadButton.Update(dt);
}

void TitleState::Render(){
	bg.Render(0, 0);
	bg.Render(bg.GetWidth(), 0);
	bg.Render(0, bg.GetHeight());
	bg.Render(bg.GetWidth(), bg.GetHeight());
	text.Render();
	startButton.Render();
	optionsButton.Render();
	quitButton.Render();
	loadButton.Render();
}

void TitleState::Input(){

	requestQuit = InputManager::GetInstance().ShouldQuit();

	if (quitButton.pressed){
		press.Play(1);
		requestQuit = true;
	}
	if (loadButton.pressed){
		press.Play(1);
		StageState* s = new StageState();
		s->Load();
		Game::GetInstance().Push(s);
		requestDelete = true;
	}
	if (optionsButton.pressed){
		press.Play(1);
		OptionsState* s = new OptionsState();
		Game::GetInstance().Push(s);
	}
	if (startButton.pressed){
		music.Stop();
		press.Play(1);
		StageState* s = new StageState();
		Game::GetInstance().Push(s);
		requestDelete = true;
	}
}


