#ifndef MusicH
#define MusicH

#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

using namespace std;

class Music {
private:
	Mix_Music* music;
	string file;
	static unordered_map<string, Mix_Music*> assetTable;

public:
	Music();
	Music(string file);
	void Play(int times);
	void Stop();
	void Open(string file);
	bool IsOpen();
	static void Clear();
};

#endif