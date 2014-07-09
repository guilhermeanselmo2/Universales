#include "OptionsState.h"


OptionsState::OptionsState() :bg("img/fundo_espaco.png"),
	text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "Cultura Univer$ales", WHITE, 100),
	resButton((Language::base[6]).c_str(), 30, 256, 300),
	fsButton(Language::base[7].c_str(), 30, 256, 370),
	langButton(Language::base[8].c_str(), 30, 256, 440),
	backButton(Language::base[9].c_str(), 30, 256, 510),
	click("music/click_interface.wav"){
	ind1 = 1;
	text.SetPos(StateData::resolution[StateData::resInd].x / 2, 60, true, true);
}


OptionsState::~OptionsState(){

}

void OptionsState::Update(float dt){
	Input();
	if (StateData::fullscreen){
		add1 = Language::base[10];
	}
	else{
		add1 = Language::base[11];
	}
	Point pt = StateData::resolution[StateData::resInd];
	add2 = to_string((int)pt.x) + "x" + to_string((int)pt.y);
	resButton.UpdateTxt((Language::base[6] + ": " + add2).c_str());
	resButton.Update(dt);
	fsButton.UpdateTxt((Language::base[7] + ": " + add1).c_str());
	fsButton.Update(dt);
	langButton.UpdateTxt((Language::base[8] + ": " + Language::names[StateData::langInd]).c_str());
	langButton.Update(dt);
	backButton.UpdateTxt(Language::base[9].c_str());
	backButton.Update(dt);

	text.SetPos(StateData::resolution[StateData::resInd].x / 2, 60, true, true);
	bg.SetClip(0, 0, StateData::resolution[StateData::resInd].x, StateData::resolution[StateData::resInd].y);
}

void OptionsState::Render(){
	bg.Render(0, 0);
	//StageState::instance->Render();
	text.Render();
	resButton.Render();
	fsButton.Render();
	langButton.Render();
	backButton.Render();
}

void OptionsState::Input(){

	requestQuit = InputManager::GetInstance().ShouldQuit();

	if (backButton.pressed){
		click.Play(1);
		requestDelete = true;
	}
	if (resButton.pressed){
		click.Play(1);
		StateData::resInd++;
		if (StateData::resInd == StateData::resolution.size()){
			StateData::resInd = 0;
		}
	}
	if (fsButton.pressed){
		click.Play(1);
		StateData::fullscreen = !StateData::fullscreen;
	}
	if (langButton.pressed){
		click.Play(1);
		StateData::langInd++;
		if (StateData::langInd == Language::names.size()){
			StateData::langInd = 0;
		}
		Language::selectLang(Language::names[StateData::langInd].c_str());
	}
}