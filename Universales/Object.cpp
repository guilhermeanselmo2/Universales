#include "Object.h"


Object::Object(int x, int y, Attributes attributes, TileMap tileMap): sp(""), tileMap(tileMap){
	this->attributes = attributes;
	tile = tileMap.GetTile(x, y);
	sp.Open(attributes.sprite);
	box = Rect(x - sp.GetWidth() / 2, y - 3*sp.GetHeight()/4, sp.GetWidth(), sp.GetHeight());

}

Object::Object(ifstream &file, TileMap tileMap) : sp(""), tileMap(tileMap){
	int size;
	file.read(reinterpret_cast<char*> (&size), sizeof(int));
	attributes.name.resize(size);
	for (int p = 0; p < attributes.name.size(); p++){
		file.read(reinterpret_cast<char*> (&attributes.name[p]), sizeof(char));
	}
	file.read(reinterpret_cast<char*> (&size), sizeof(int));
	attributes.type.resize(size);
	for (int p = 0; p < size; p++){
		file.read(reinterpret_cast<char*> (&attributes.type[p]), sizeof(char));
	}
	file.read(reinterpret_cast<char*> (&size), sizeof(int));
	attributes.sprite.resize(size);
	for (int p = 0; p < size; p++){
		file.read(reinterpret_cast<char*> (&attributes.sprite[p]), sizeof(char));
	}
	file.read(reinterpret_cast<char*> (&size), sizeof(int));
	attributes.description.resize(size);
	for (int p = 0; p < size; p++){
		file.read(reinterpret_cast<char*> (&attributes.description[p]), sizeof(char));
	}
	file.read(reinterpret_cast<char*> (&attributes.cost), sizeof(int));
	file.read(reinterpret_cast<char*> (&attributes.activeHunger), sizeof(int));
	file.read(reinterpret_cast<char*> (&attributes.activeSatisfaction), sizeof(float));
	file.read(reinterpret_cast<char*> (&attributes.activeMoney), sizeof(int));
	file.read(reinterpret_cast<char*> (&attributes.radius), sizeof(int));
	file.read(reinterpret_cast<char*> (&attributes.passiveHunger), sizeof(int));
	file.read(reinterpret_cast<char*> (&attributes.passiveSatisfaction), sizeof(float));
	file.read(reinterpret_cast<char*> (&attributes.passiveMoney), sizeof(int));
	file.read(reinterpret_cast<char*> (&box), sizeof(Rect));
	file.read(reinterpret_cast<char*> (&tile), sizeof(Point));
	sp.Open(attributes.sprite);
}

void Object::Save(ofstream &file){
	int size = attributes.name.size();
	file.write(reinterpret_cast<char*> (&size), sizeof(int));
	for (int p = 0; p < attributes.name.size(); p++){
		file.write(reinterpret_cast<char*> (&attributes.name[p]), sizeof(char));
	}
	size = attributes.type.size();
	file.write(reinterpret_cast<char*> (&size), sizeof(int));
	for (int p = 0; p < size; p++){
		file.write(reinterpret_cast<char*> (&attributes.type[p]), sizeof(char));
	}
	size = attributes.sprite.size();
	file.write(reinterpret_cast<char*> (&size), sizeof(int));
	for (int p = 0; p < size; p++){
		file.write(reinterpret_cast<char*> (&attributes.sprite[p]), sizeof(char));
	}
	size = attributes.description.size();
	file.write(reinterpret_cast<char*> (&size), sizeof(int));
	for (int p = 0; p < size; p++){
		file.write(reinterpret_cast<char*> (&attributes.description[p]), sizeof(char));
	}
	file.write(reinterpret_cast<char*> (&attributes.cost), sizeof(int));
	file.write(reinterpret_cast<char*> (&attributes.activeHunger), sizeof(int));
	file.write(reinterpret_cast<char*> (&attributes.activeSatisfaction), sizeof(float));
	file.write(reinterpret_cast<char*> (&attributes.activeMoney), sizeof(int));
	file.write(reinterpret_cast<char*> (&attributes.radius), sizeof(int));
	file.write(reinterpret_cast<char*> (&attributes.passiveHunger), sizeof(int));
	file.write(reinterpret_cast<char*> (&attributes.passiveSatisfaction), sizeof(float));
	file.write(reinterpret_cast<char*> (&attributes.passiveMoney), sizeof(int));
	file.write(reinterpret_cast<char*> (&box), sizeof(Rect));
	file.write(reinterpret_cast<char*> (&tile), sizeof(Point));
}



Object::~Object(){
}


void Object::Render(int cameraX, int cameraY){
	sp.Render(box.x + Camera::pos.x, box.y + Camera::pos.y);
}

void Object::Update(float dt){

}

void Object::MoveTo(int x, int y){
	tile = tileMap.GetTile(x, y);
	Point pos = tileMap.GetTileCenter(tile);
	box = Rect(pos.x - sp.GetWidth() / 2, pos.y - 3 * sp.GetHeight() / 4, sp.GetWidth(), sp.GetHeight());
}

bool Object::IsDead(){
	return false;
}

bool Object::Is(string type){
	return type == "Object";
}


void Object::Editing(bool editing){

}
void Object::AddObjective(float x, float y, Point tile){

}
void Object::AddObjective(vector<int> path){

}

bool Object::IsCharacter(){
	return false;
}

string Object::Type(){
	return "Object";
}

Choice Object::GetChoice(){
	return DECIDING;
}

int Object::GetHunger(){
	return 0;
}
