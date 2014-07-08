#include "Language.h"


Language::Language()
{
}


Language::~Language()
{
}

vector<string> Language::base;
vector<string> Language::names = { "pt-br", "en" };
void Language::selectLang(string lang){
	base.resize(12);
	if (lang == "pt-br"){
		base[0] = "Comecar";
		base[1] = "Opcoes";
		base[2] = "Carregar";
		base[3] = "Sair";
		base[4] = "Continuar";
		base[5] = "Salvar";
		base[6] = "Resolucao";
		base[7] = "Tela cheia";
		base[8] = "Idioma";
		base[9] = "Voltar";
		base[10] = "ligado";
		base[11] = "desligado";
	}
	if (lang == "en"){
		base[0] = "Start";
		base[1] = "Options";
		base[2] = "Load";
		base[3] = "Quit";
		base[4] = "Resume";
		base[5] = "Save";
		base[6] = "Resolution";
		base[7] = "Fullscreen";
		base[8] = "Language";
		base[9] = "Back";
		base[10] = "on";
		base[11] = "off";
	}
}