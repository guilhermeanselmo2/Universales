#include "Music.h"
#include <iostream>

unordered_map<string, Mix_Music*> Music::assetTable;

Music::Music() {
	music = NULL;
}

Music::Music(string file) {
	Open(file);
}

void Music::Play(int times) {
	isOverInd = false;
	Mix_FadeInMusic(music,times,1000);
	Mix_HookMusicFinished(*Music::musicFinished);
}

void Music::Stop() {
	Mix_FadeOutMusic(1000);
}

void Music::Open(string file) {
	isOverInd = false;

	if (assetTable.find(file) != assetTable.end()){
		//std::cout << "Arquivo carregado ..." << std::endl;
	}

	if (assetTable.find(file) == assetTable.end()){
		//std::cout << "Arquivo nao encontrado... carregando arquivo... " << std::endl;
		music = Mix_LoadMUS(file.c_str());
		assetTable.emplace(file, music);
	}

	music = assetTable.at(file);
}

bool Music::IsOpen() {
	if (music != NULL)
		return true;
	return false;
}

void Music::Clear() {
	for (auto element = assetTable.begin(); element != assetTable.end(); element++) {
		Mix_FreeMusic(element->second);
	}
}

void Music::musicFinished(){
	isOverInd = true;
	cout << "terminou" << endl;
}

bool Music::isOverInd = false;

void Music::SetVolume(int vol){
	if ((vol >= 0) && (vol <= 128))
		Mix_VolumeMusic(vol);
}