#include "Permonkey.h"
#include "Camera.h"

Permonkey::Permonkey(float x, float y, Point lTile, TileMap tileMap) : character("img/permacaco_anim_ss.png", 4, -1, 4), tileMap(tileMap) {

    box = Rect(x-character.GetWidth()/2,y-character.GetHeight(), character.GetWidth(), character.GetHeight());
	rotation = 0;
	roomID = 0;
	crt = 0;
	objective.x = 994;
	objective.y = 470;
	tile = lTile;
	actionCharacter = Character::RESTING;
	
}

Permonkey::~Permonkey(){


}

void Permonkey::Update(float dt){
	switch (actionCharacter) {
	case Character::RESTING:
		character.SetFrameTime(-1);
		character.Update(dt);
		break;
	case Character::MOVING:
		character.SetFrameTime(0.5);
		character.Update(dt);
		Move(dt);
		break;
	}
}

void Permonkey::Render(int cameraX, int cameraY){
    character.Render(box.x+Camera::pos.x, box.y+Camera::pos.y, rotation);
}

bool Permonkey::IsDead(){
	return false;

}

void Permonkey::NotifyCollision(GameObject &other){

}

void Permonkey::Editing(bool edit) {}

bool Permonkey::Is(string type){
    return type == "PerMonkey";
}

bool Permonkey::IsCharacter(){
	return false;
}

string Permonkey::Type(){
    return "PerMonkey";
}

void Permonkey::AddObjective(float x, float y, Point tile){
	cout << "Add 1" << endl;
	if (crt >= 0)
		crt++;
	objective.x = x;
	objective.y = y;
	objectiveTile = tile;

	cout << "tile x: " << tile.x << "tile y:" << tile.y << endl;

	if ((tile.x >= 0) && (tile.y >= 0)) {
		actionCharacter = Character::MOVING;
		flagDesvio = false;
	}
}

void Permonkey::AddObjective(Point pos){
	cout << "Add 2" << endl;
    if (crt >= 0)
        crt++;
    objective = pos;
	actionCharacter = Character::MOVING;
	flagDesvio = false;
}

void Permonkey::AddObjective(vector<int> path) {
	cout << "Add 3" << endl;
	this->path = path;
	if (crt >= 0)
		crt++;
	this->path.pop_back();
	this->path.pop_back();
	actionCharacter = Character::MOVING;
	flagDesvio = false;
}


void Permonkey::Go(Point pos){
	cout << "Go 1" << endl;
    objective = pos;
}

void Permonkey::PathAStar(Point pos, vector<int> heuristic, vector<int> occupancyGrid){
	PathAStar(pos.x, pos.y, heuristic, occupancyGrid);

}

void Permonkey::PathAStar(int posX, int posY, vector<int> heuristic, vector<int> occupancyGrid){

}

void Permonkey::Move(float dt){
	temp.Update(dt);
	Point center_pos;
	center_pos.x = box.x + character.GetWidth() / 2;
    center_pos.y = box.y + character.GetHeight();
	float distance = objective.GetDistance(box.x + character.GetWidth() / 2, box.y + character.GetHeight());
	if ((objectiveTile.x >= 0) && (objectiveTile.y >= 0)) {
		if (distance < 8) {
			box.x = objective.x;
			box.y = objective.y;
			box = Rect(box.x - character.GetWidth() / 2, box.y - character.GetHeight(), character.GetWidth(), character.GetHeight());
			actionCharacter = Character::RESTING;
			if (!path.empty()) {
				path.pop_back();
				objective.y = (int)(path[path.size()] / tileMap.GetWidth());
				objective.x = path[path.size()] % tileMap.GetWidth();
				objective = tileMap.GetTileCenter(objective);
				objectiveTile = tileMap.GetTile(objective.x, objective.y);
				actionCharacter = Character::MOVING;
			}
			if (flagDesvio){
				objective.x = objectiveMem.x;
				objective.y = objectiveMem.y;
				flagDesvio = false;
				actionCharacter = Character::MOVING;
			}
		}

		if (distance > 3 && temp.Get() > 0.001) {
			if (((objective.x != center_pos.x) || (objective.y != center_pos.y)) && ((objective.y > 0) && (objective.x > 0))) {
				permonkeyTile = tileMap.GetTile(center_pos.x, center_pos.y);
				if ((objective.x != center_pos.x) && (objective.y != center_pos.y)) {

					if ((center_pos.x < objective.x) && (center_pos.y < objective.y)){
						character.SetCurrentHeight(0);
						box.x += 2;
						box.y += 1;
					}
					if ((center_pos.x > objective.x) && (center_pos.y < objective.y)){
						character.SetCurrentHeight(1);
						box.x -= 2;
						box.y += 1;
					}

					if ((center_pos.x < objective.x) && (center_pos.y > objective.y)){
						character.SetCurrentHeight(2);
						box.x += 2;
						box.y -= 1;
					}
					if ((center_pos.x > objective.x) && (center_pos.y > objective.y)){
						character.SetCurrentHeight(3);
						box.x -= 2;
						box.y -= 1;
					}
				}

				if ((objective.x == center_pos.x) && (objective.y != center_pos.y)) {
					if ((center_pos.y < objective.y)){
						flagDesvio = true;
						objectiveMem = objective;
						desvio.SetPoint(objectiveTile.x, permonkeyTile.y);
						objective.x = tileMap.GetTileCenter(desvio).x;
						objective.y = tileMap.GetTileCenter(desvio).y;
					}

					if ((center_pos.y > objective.y)){
						flagDesvio = true;
						objectiveMem = objective;
						desvio.SetPoint(permonkeyTile.x, objectiveTile.y);
						objective.x = tileMap.GetTileCenter(desvio).x;
						objective.y = tileMap.GetTileCenter(desvio).y;
					}
				}
				if ((objective.x != center_pos.x) && (objective.y == center_pos.y)) {
					if ((center_pos.x < objective.x)){
						flagDesvio = true;
						objectiveMem = objective;
						desvio.SetPoint(permonkeyTile.x, objectiveTile.y);
						objective.x = tileMap.GetTileCenter(desvio).x;
						objective.y = tileMap.GetTileCenter(desvio).y;
					}

					if ((center_pos.x > objective.x)){
						flagDesvio = true;
						objectiveMem = objective;
						desvio.SetPoint(objectiveTile.x, permonkeyTile.y);
						objective.x = tileMap.GetTileCenter(desvio).x;
						objective.y = tileMap.GetTileCenter(desvio).y;
					}
				}
			}

			else {
				//Stop;
			}
			//box = Rect(tile_pos.x-character.GetWidth()/2,tile_pos.y-character.GetHeight()/2, character.GetWidth(), character.GetHeight());
			temp.Restart();
		}
	}
}
