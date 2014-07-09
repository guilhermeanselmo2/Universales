#include "Permonkey.h"
#include "Camera.h"
#include "Object.h"

Permonkey::Permonkey(float x, float y, Point lTile, TileMap tileMap, unordered_map<string, vector<string>> objList) : character("img/permacaco_anim_ss.png", 4, -1, 4), tileMap(tileMap),
step("music/passo_et_verde.wav") {
    box = Rect(x-character.GetWidth()/2,y-character.GetHeight(), character.GetWidth(), character.GetHeight());
	rotation = 0;
	roomID = 0;
	crt = 0;
	objective.x = 994;
	objective.y = 470;
	tile = lTile;
	actionCharacter = RESTING;
	choice = NO_CHOICE;
	timer.Restart();
	rest.Restart();

	hunger = rand()%21;
	money = rand()%900+101;
	found = true;
	satisfaction = 50;

	preference = "Pirate";
	roomChoice = "";
	actualGoal = 0;

	Classify(objList);

	gone = false;
	

	objectSelect = -1;
	
	
}

Permonkey::Permonkey(ifstream &file, TileMap tileMap, unordered_map<string, vector<string>> objList) : 
character("img/permacaco_anim_ss.png", 4, -1, 4), tileMap(tileMap) {
	file.read(reinterpret_cast<char*> (&box), sizeof(Rect));
	file.read(reinterpret_cast<char*> (&rotation), sizeof(float));
	file.read(reinterpret_cast<char*> (&roomID), sizeof(int));
	file.read(reinterpret_cast<char*> (&crt), sizeof(int));
	file.read(reinterpret_cast<char*> (&objective), sizeof(Point));
	file.read(reinterpret_cast<char*> (&tile), sizeof(Point));
	file.read(reinterpret_cast<char*> (&actionCharacter), sizeof(ActionCharacter));
	file.read(reinterpret_cast<char*> (&choice), sizeof(Choice));
	file.read(reinterpret_cast<char*> (&hunger), sizeof(int));
	file.read(reinterpret_cast<char*> (&money), sizeof(int));
	file.read(reinterpret_cast<char*> (&found), sizeof(bool));
	file.read(reinterpret_cast<char*> (&satisfaction), sizeof(int));
	file.read(reinterpret_cast<char*> (&actualGoal), sizeof(int));
	file.read(reinterpret_cast<char*> (&objectSelect), sizeof(int));
	int size;
	file.read(reinterpret_cast<char*> (&size), sizeof(int));
	preference.resize(size);
	for (int p = 0; p < preference.size(); p++){
		file.read(reinterpret_cast<char*> (&preference[p]), sizeof(char));
	}
	file.read(reinterpret_cast<char*> (&size), sizeof(int));
	roomChoice.resize(size);
	for (int p = 0; p < roomChoice.size(); p++){
		file.read(reinterpret_cast<char*> (&roomChoice[p]), sizeof(char));
	}
	file.read(reinterpret_cast<char*> (&timer), sizeof(Timer));
	file.read(reinterpret_cast<char*> (&rest), sizeof(Timer));
	Classify(objList);
}
void Permonkey::Save(ofstream &file){
	file.write(reinterpret_cast<char*> (&box), sizeof(Rect));
	file.write(reinterpret_cast<char*> (&rotation), sizeof(float));
	file.write(reinterpret_cast<char*> (&roomID), sizeof(int));
	file.write(reinterpret_cast<char*> (&crt), sizeof(int));
	file.write(reinterpret_cast<char*> (&objective), sizeof(Point));
	file.write(reinterpret_cast<char*> (&tile), sizeof(Point));
	file.write(reinterpret_cast<char*> (&actionCharacter), sizeof(ActionCharacter));
	file.write(reinterpret_cast<char*> (&choice), sizeof(Choice));
	file.write(reinterpret_cast<char*> (&hunger), sizeof(int));
	file.write(reinterpret_cast<char*> (&money), sizeof(int));
	file.write(reinterpret_cast<char*> (&found), sizeof(bool));
	file.write(reinterpret_cast<char*> (&satisfaction), sizeof(int));
	file.write(reinterpret_cast<char*> (&actualGoal), sizeof(int));
	file.write(reinterpret_cast<char*> (&objectSelect), sizeof(int));
	int size = preference.size();
	file.write(reinterpret_cast<char*> (&size), sizeof(int));
	for (int p = 0; p < preference.size(); p++){
		file.write(reinterpret_cast<char*> (&preference[p]), sizeof(char));
	}
	size = roomChoice.size();
	file.write(reinterpret_cast<char*> (&size), sizeof(int));
	for (int p = 0; p < roomChoice.size(); p++){
		file.write(reinterpret_cast<char*> (&roomChoice[p]), sizeof(char));
	}
	file.write(reinterpret_cast<char*> (&timer), sizeof(Timer));
	file.write(reinterpret_cast<char*> (&rest), sizeof(Timer));
}
Permonkey::~Permonkey(){


}

void Permonkey::Update(float dt, vector<unique_ptr<GameObject>> *objectArray){
	timer.Update(dt);
	if (timer.Get() > 6){
		hunger += 1;
		timer.Restart();
	}
	switch (actionCharacter) {
	case RESTING:
		rest.Update(dt);
		if (rest.Get() > 3){
			rest.Restart();
			if (arrived && found)
				actionCharacter = DECIDING_OBJECT;
			if (arrived && !found)
				actionCharacter = USING_OBJECT;
		}

		character.SetFrameTime(-1);
		character.Update(dt);
		if (arrived){

		}
		break;
	case MOVING:
		soundControl += dt;
		character.SetFrameTime(0.5);
		if (soundControl >= 0.5){
			step.Play(1);
			soundControl = 0;
		}
		character.Update(dt);
		Move(dt);
		break;
	case DECIDING_ROOM:
		if (choice == NO_CHOICE){
			MakeChoice();
		}
		break;
	case DECIDING_OBJECT:
		if (objectSelect == -1){
			SearchObject(objectArray);
		}
		break;
	case USING_OBJECT:
		rest.Update(dt);
		if (rest.Get() > 5){
			UseObject(objectArray, objectSelect);
			rest.Restart();
			actionCharacter = RESTING;
			found = true;
		}
		break;
	case EXITING:
		SearchObject(objectArray);
		cout << arrived << endl;
		if (arrived){
			gone = true;
		}
		cout << found << endl;
		break;
	}
	//tile = tileMap.GetTile(box.x+box.w/2, box.y+box.y);
}

string Permonkey::GetChoice(){
	return goals[actualGoal].first;
}

void Permonkey::Render(int cameraX, int cameraY){
    character.Render(box.x+Camera::pos.x, box.y+Camera::pos.y, rotation);
}

bool Permonkey::IsDead(){
	return gone;

}

void Permonkey::NotifyCollision(GameObject &other){

}

void Permonkey::Editing(bool edit) {}

bool Permonkey::Is(string type){
    return type == "PerMonkey";
}

bool Permonkey::IsCharacter(){
	return true;
}

int Permonkey::GetHunger(){
	return hunger;
}

void Permonkey::SetHunger(int hunger){
	this->hunger = hunger;
}

string Permonkey::Type(){
    return "PerMonkey";
}

void Permonkey::AddObjective(float x, float y, Point tile){
	if (crt >= 0)
		crt++;
	objective.x = x;
	objective.y = y;
	objectiveTile = tile;


	if ((tile.x >= 0) && (tile.y >= 0)) {
		actionCharacter = MOVING;
		flagDesvio = false;
	}
}

void Permonkey::AddObjective(Point pos){
    if (crt >= 0)
        crt++;
    objective = pos;
	actionCharacter = MOVING;
	flagDesvio = false;
}

void Permonkey::AddObjective(vector<int> path) {
	this->path = path;
	switch (choice)	{
	case PIRATE_C:
		choice = GOING_P;
		break;
	case SAMURAI_C:
		choice = GOING_S;
		break;
	default:
		break;
	}
	if (crt >= 0)
		crt++;
	//this->path.pop_back();
	//this->path.pop_back();
	//cout << "U_Path :: " << path[path.size()-1] % tileMap.GetWidth() << "," << (int)path[path.size()-1] / tileMap.GetWidth() << endl;
	objective.y = (int)(path[path.size()-1] / tileMap.GetWidth());
	objective.x = path[path.size()-1] % tileMap.GetWidth();
	objective = tileMap.GetTileCenter(objective);
	objectiveTile = tileMap.GetTile(objective.x, objective.y);
	path.pop_back();
	actionCharacter = MOVING;
	flagDesvio = false;
}


void Permonkey::Go(Point pos){
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
			actionCharacter = RESTING;
			if (!path.empty()) {
				objective.y = (int)(path[path.size()-1] / tileMap.GetWidth());
				objective.x = path[path.size()-1] % tileMap.GetWidth();
				objective = tileMap.GetTileCenter(objective);
				objectiveTile = tileMap.GetTile(objective.x, objective.y);
				actionCharacter = MOVING;
				path.pop_back();
			}
			else{
				arrived = true;
			}
			if (flagDesvio){
				objective.x = objectiveMem.x;
				objective.y = objectiveMem.y;
				flagDesvio = false;
				actionCharacter = MOVING;
			}
		}

		if (distance > 3 && temp.Get() > 0.001) {
			if (((objective.x != center_pos.x) || (objective.y != center_pos.y)) && ((objective.y > 0) && (objective.x > 0))) {
				permonkeyTile = tileMap.GetTile(center_pos.x, center_pos.y);
				tile = permonkeyTile;
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

void Permonkey::MakeChoice(){
	bool sameRoom = false;
	if (!goals.empty()){
		if (roomChoice == ""){
			roomChoice = goals[0].first;
		}
		else{
			actualGoal++;
			for (int i = actualGoal; i < goals.size(); i++){
				if (goals[i].first == roomChoice){
					sameRoom = true;
					break;
				}
			}
			if (sameRoom == false){
				roomChoice = goals[actualGoal].first;
			}

		}
	}
	else{
		actionCharacter = EXITING;
	}
}

bool Permonkey::SettlePos(vector<int> obstacleMap){
	return false;
}

void Permonkey::MoveTo(int x, int y){
	box = Rect(x - character.GetWidth() / 2, y - character.GetHeight(), character.GetWidth(), character.GetHeight());
}

int Permonkey::SearchObject(vector<unique_ptr<GameObject>> *objectArray){
	found = false;
	int object = -1;
	if (goals.empty()){
		actionCharacter = EXITING;
		for (int i = 0; i < objectArray->size(); i++){
			if (objectArray->at(i)->Is("Object")){
				if (objectArray->at(i)->GetTextAttributes()[0] == "Teleporter"){
					cout << "Last Object = " << i << endl;

					object = i;
				}
			}
		}
		cout << "New object select : " << object << endl;;
	}
	else{
		for (int i = 0; i < objectArray->size(); i++){
			if (objectArray->at(i)->Is("Object")){
				if (objectArray->at(i)->GetTextAttributes()[0] == goals[actualGoal].second){
					cout << "Object = " << i << endl;
					object = i;
				}
			}
		}
	}
	objectSelect = object;
	return object;
}

ActionCharacter Permonkey::GetAction(){
	return actionCharacter;
}


int Permonkey::GetObjectIndex(){
	return objectSelect;
}

vector<int> Permonkey::GetHeuristic(int i){
	vector<int> a;
	return a;
}

vector<int> Permonkey::GetAttributes(){
	vector<int> a;
	return a;
}

void Permonkey::UseObject(vector<unique_ptr<GameObject>> *objectArray, int index){
	cout << "Index : " << index << endl;
	vector<pair<string, string>> newGoals;
	if (index >= 0){
		vector<int> activeAttributes = objectArray->at(index)->GetAttributes();
		hunger -= activeAttributes[0];
		money -= activeAttributes[1];
		satisfaction += activeAttributes[2];
		objectSelect = -1;
		goals[actualGoal].first = "";
		for (int i = 0; i < goals.size(); i++){
			if (goals[i].first != ""){
				newGoals.emplace_back(goals[i]);
			}
		}
		goals = newGoals;
		cout << "New Size : " << goals.size() << endl;

	}
	else{
		cout << "ERROR: Permonkey UseObject method: Index is less than 0" << endl;
	}
}

vector<Point> Permonkey::GetAccessPoints(){
	vector<Point> a;
	return a;
}

vector<string> Permonkey::GetTextAttributes(){
	vector<string> a;
	return a;
}

Rect Permonkey::GetBox(){
	return box;
}

void Permonkey::Classify(unordered_map<string, vector<string>> objList){
	pair<string, string> nameType;

	for (auto i = objList.begin(); i != objList.end(); ++i){
		for (int j = 0; j < i->second.size(); j++){
			if (i->first == preference){
				nameType.first = i->first;
				nameType.second = i->second[j];
				preferredObjects.emplace_back(nameType);
			}
			else{
				if (i->first != "None"){
					nameType.first = i->first;
					nameType.second = i->second[j];
					otherObjects.emplace_back(nameType);
				}
				else{
					lastGoal.first = i->first;
					lastGoal.second = i->second[j];
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
		ChooseGoals();
	for (int i = 0; i < goals.size(); i++){
		//cout << goals[i].first << " : " << goals[i].second << endl;
	}
}

void Permonkey::ChooseGoals(){
	int typeChoice = rand() % 101;
	int objChoice;
	vector<pair<string, string>> newVector;
	
	if (typeChoice <= 60 && preferredObjects.size()>0){
		objChoice = rand() % preferredObjects.size();
		goals.emplace_back(preferredObjects[objChoice]);
		preferredObjects[objChoice].first = "";
		for (int i = 0; i < preferredObjects.size(); i++){
			if (preferredObjects[i].first != "")
				newVector.emplace_back(preferredObjects[i]);
		}
		preferredObjects = newVector;
		
	}
	else{
		if (otherObjects.size() > 0 ){
			cout << "Entrou other" << otherObjects.size() << endl;
			objChoice = rand() % otherObjects.size();
			goals.emplace_back(otherObjects[objChoice]);
			otherObjects[objChoice].first = "";
			otherObjects.shrink_to_fit();

			for (int i = 0; i < otherObjects.size(); i++){
				if (otherObjects[i].first != "")
					newVector.emplace_back(otherObjects[i]);
			}
			otherObjects = newVector;
		}
	}
}

Point Permonkey::GetTile(){
	return tile;
}

void Permonkey::ChangeSelection(int reference){
	if (objectSelect == reference){
		objectSelect = -1;
	}
	if (objectSelect > reference){
		objectSelect--;
	}
}