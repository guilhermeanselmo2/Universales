#include "Sound.h"
#include <iostream>

unordered_map<string, Mix_Chunk*> Sound::assetTable;

Sound::Sound() {
	chunk = NULL;
}

Sound::Sound(string file) {
	Open(file);
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

void Sound::Open(string file) {
	if (assetTable.find(file) != assetTable.end()){
		std::cout << "Arquivo carregado ..." << std::endl;
	}

	if (assetTable.find(file) == assetTable.end()){
		std::cout << "Arquivo nao encontrado... carregando arquivo... " << std::endl;
		chunk = Mix_LoadWAV(file.c_str());
		assetTable.emplace(file, chunk);
	}

	chunk = assetTable.at(file);
}

void Sound::Clear() {
	for (auto element = assetTable.begin(); element != assetTable.end(); element++) {
		Mix_FreeChunk(element->second);
	}
}