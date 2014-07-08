#include "StateData.h"

int StateData::langInd = 1;
bool StateData::fullscreen = false;
vector<Point> StateData::resolution = { Point(800, 600), Point(1024, 768), Point(1440, 960) };
int StateData::resInd = 0;

void StateData::GetSysData(){
	ifstream readFile("config.bin", ios::in | ios::binary);
	if (readFile.is_open()){
		readFile.read(reinterpret_cast<char*> (&langInd), sizeof(int));
		readFile.read(reinterpret_cast<char*> (&fullscreen), sizeof(bool));
		readFile.read(reinterpret_cast<char*> (&resInd), sizeof(int));
	}
	else{
		langInd = 1;
		fullscreen = false;
		resInd = 0;
	}
	readFile.close();
}
void StateData::SaveSysData(){
	ofstream saveFile("config.bin", ios::out | ios::binary);
	saveFile.write(reinterpret_cast<char*> (&langInd), sizeof(int));
	saveFile.write(reinterpret_cast<char*> (&fullscreen), sizeof(bool));
	saveFile.write(reinterpret_cast<char*> (&resInd), sizeof(int));
	saveFile.close();
}