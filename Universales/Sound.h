#ifndef SoundH
#define SoundH

#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

using namespace std;

class Sound {
private:
	Mix_Chunk* chunk; 
	int channel;
	string file;
	static unordered_map<string, Mix_Chunk*> assetTable;

public:
	Sound();
	Sound(string file);
	void Play(int times);
	void Stop();
	void Open(string file);
	bool IsOpen();
	static void Clear();
};

#endif