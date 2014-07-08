#include "PauseState.h"


PauseState::PauseState() :bg("img/fundo_espaco.png"),
text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "Cultura Univer$ale", WHITE, 100),
resumeButton(Language::base[4].c_str() , 30, 256, 300),
	optionsButton(Language::base[1].c_str(), 30, 256, 370),
	saveButton(Language::base[5].c_str(), 30, 256, 440),
	quitButton(Language::base[3].c_str(), 30, 256, 510),
	click("music/click_interface.wav"){
	text.SetPos(512, 60, true, true);
	StageState::instance->music.SetVolume(24);
}


PauseState::~PauseState()
{
}

void PauseState::Update(float dt){
	Input();
	resumeButton.UpdateTxt(Language::base[4].c_str());
	resumeButton.Update(dt);
	optionsButton.UpdateTxt(Language::base[1].c_str());
	optionsButton.Update(dt);
	quitButton.UpdateTxt(Language::base[3].c_str());
	quitButton.Update(dt);
	saveButton.UpdateTxt(Language::base[5].c_str());
	saveButton.Update(dt);

	text.SetPos(StateData::resolution[StateData::resInd].x / 2, 60, true, true);
	bg.SetClip(0, 0, StateData::resolution[StateData::resInd].x, StateData::resolution[StateData::resInd].y);
}

void PauseState::Render(){
	bg.Render(0, 0);
	//StageState::instance->Render();
	text.Render();
	resumeButton.Render();
	optionsButton.Render();
	quitButton.Render();
	saveButton.Render();
}

void PauseState::Input(){

	requestQuit = InputManager::GetInstance().ShouldQuit();

	if (quitButton.pressed){
		click.Play(1);
		requestQuit = true;
	}
	if (resumeButton.pressed){
		click.Play(1);
		StageState::instance->music.SetVolume(128);
		requestDelete = true;
	}
	if (optionsButton.pressed){
		click.Play(1);
		OptionsState* s = new OptionsState();
		Game::GetInstance().Push(s);
	}
	if (saveButton.pressed){
		click.Play(1);
		//deveria passar alguma msg para a tela.
		StageState::instance->Save();
		requestDelete = true;
	}
}
