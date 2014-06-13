#include "StageState.h"
#include "EndState.h"
#include "Alien.h"
#include "Penguins.h"
#include "Music.h"
#include "StateData.h"
#include "Permonkey.h"
#include "CostComparator.h"


StageState::StageState() : tileSet(152,76), tileMap("map/tileMap.txt", &tileSet),
moneyText("font/enhanced_dot_digital-7.ttf", 40, Text::TEXT_BLENDED, "-", WHITE, 100), occupancyMap(tileMap.GetWidth(), tileMap.GetWidth()), subGuiEdit("img/icons/door.png", "img/icons/wall.jpg") {
	string file, tile, line, endLine("\n"), initFile("img/tileset/");
	FILE *tileFile;
	Point roomBegin, roomEnd;
	char c;

	creationTimer.Restart();

	rType = CORRIDOR;

	roomBegin.SetPoint(0, 0);
	roomEnd.SetPoint(25, 25);

	action = NONE;

	bg.Open("img/fundo_espaco.png");
	Music musica("audio/stageState.ogg");
	//musica.Play(-1);
	//Penguins* penguin = new Penguins(100, 300);
	//Alien* alien = new Alien(800, 300, 6);
	//Alien* alien2 = new Alien(100, 100, 6);
	//Alien* alien3 = new Alien(100, 500, 6);
	//Camera::Follow(penguin);
	//objectArray.emplace_back(penguin);
	//objectArray.emplace_back(alien);
	//objectArray.emplace_back(alien2);
	//objectArray.emplace_back(alien3);

	Point monkeyTile(4,4);
	Point teste(0, 0);
    monkeyTile = tileMap.GetTileCenter(monkeyTile);
    Permonkey* pM = new Permonkey(monkeyTile.x, monkeyTile.y, teste, tileMap);
    objectArray.emplace_back(pM);

	//Room *newRoom = new Room(roomBegin, roomEnd, &tileMap, &objectArray, roomArray.size(), rType);
	//roomArray.emplace_back(newRoom);

	file = "img/tileset/tilelist.txt";
    tileFile = fopen(file.c_str(),"r");
    if(tileFile == NULL)
        exit(EXIT_FAILURE);

    while (!feof(tileFile)) {
        fscanf(tileFile, "%c", &c);
        line = c;
        while(line.find(endLine)== string::npos){
            fscanf(tileFile, "%c", &c);
            line = line + c;
        }

        line.pop_back();
        tile = initFile+line;
        if(tile.compare(initFile)!= 0)
            tileSet.Open(tile);
    }
	data = new StateData();
	data->money = 0;
	data->fame = 0;
	moneyText.SetText(to_string(data->money));
	moneyText.SetPos(20, 20, false, false);
}

StageState::~StageState() {
	delete data;
	objectArray.clear();
	roomArray.clear();
	//Music::Clear();
	//Sprite::Clear();
}

void StageState::Update(float dt) {
	Input();
	creationTimer.Update(dt);
	switch (action)	{
	case NONE:
		break;
	case TILE_SELECT:
		p = tileMap.GetTile(InputManager::GetInstance().GetMouseX()-Camera::pos.x,InputManager::GetInstance().GetMouseY()-Camera::pos.y);
        selectionBox.SetBegin(p);
		selectionBox.Update(&tileMap);
        p = tileMap.GetTileCenter(p);
		break;
	case CONSTRUCT_ROOM:
		selectionBox.Update(&tileMap);
		break;
	case DESTROY_ROOM:
		break;
	case AREA_SELECT:
		break;
	default:
		break;
	}
	UpdateArray(dt,&tileMap);
	
	for (int i = 0; i < objectArray.size(); i++){
		
		if (objectArray[i]->IsCharacter() && objectArray[i]->GetChoice() != GOING_P && objectArray[i]->GetChoice() != GOING_S){
			charChoice = objectArray[i]->GetChoice();
			charRoom = CORRIDOR;
			if (charChoice == PIRATE_C){
				charRoom = PIRATE;
			}
			if (charChoice == SAMURAI_C){
				charRoom = SAMURAI;
			}
			if (!roomArray.empty()){
				for (int j = 0; j < roomArray.size(); j++){
					if ((roomArray[j]->GetState() == charRoom) && (roomArray[j]->roomState != Room::EDITING)){
						int x, y;
						Point t;
						x = objectArray[i]->box.x + objectArray[i]->box.w / 2;
						y = objectArray[i]->box.y + objectArray[i]->box.h;
						t = tileMap.GetTile(x, y);
						objectArray[i]->AddObjective(PathAStar(t.x, t.y, roomArray[j]->GetID()));
					}
				}
			}
		}
	}
	if (creationTimer.Get() > 5){
		CreateCharacter(5, 5);
		creationTimer.Restart();
	}
	
}

void StageState::Render() {
	bg.Render(0, 0);
	tileMap.Render(Camera::pos.GetXpoint(), Camera::pos.GetYpoint());

	moneyText.SetText(to_string(data->money));
	moneyText.SetPos(20, 20, false, false);
	moneyText.Render();

	SDL_Rect fillRect = { 20, 70, 100, 10 };
	if (data->fame <= 255){
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255 - data->fame, 0, data->fame, 255);
	}
	if (data->fame >= 255){
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 255, 255);
	}
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &fillRect);
	
	for(int i = 0; i < roomArray.size(); i++){
        roomArray[i]->Render(&tileMap);
    }
	switch (action)	{
	case NONE:
		RenderArray();
		occupancyMap.Render(&tileMap);
		break;
	case TILE_SELECT:
		selectionBox.Render(&tileMap);
		RenderArray();
		break;
	case GUI_ROOM:
		RenderArray();
		gui.Render();
		break;
	case CONSTRUCT_ROOM:
		selectionBox.Render(&tileMap);
		RenderArray();
		break;
	case DESTROY_ROOM:
		RenderArray();
		break;
	case AREA_SELECT:
		RenderArray();
		break;
	case GUI_A:
		RenderArray();
		gui.Render();
		break;
	case SUB_GUI_EDIT :
		RenderArray();
		subGuiEdit.Render();
		break;
	case EDIT_DOOR:
		RenderArray();
		break;
	default:
		RenderArray();
		break;
	}
	
}

void StageState::Input() {
	if ((InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) || (InputManager::GetInstance().ShouldQuit())){
		PauseState *state = new PauseState();
		Game::GetInstance().Push(state);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_c)){
		Point tile(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
		tile = tileMap.GetTile(tile.x, tile.y);
		CreateCharacter(tile.x, tile.y);
		cout << "Size : " << objectArray.size() << endl;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_d)){
		DestroyCharacter(objectArray.size()-1);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_RETURN)){
		CheatState *state = new CheatState(this, data);
		Game::GetInstance().Push(state);
	}
	if(InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){

		switch (action){
		case NONE:
			ptile = tileMap.GetTile(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);
			p = tileMap.GetTileCenter(ptile);
			objectArray[0]->AddObjective(p.x, p.y, ptile);
			for (int i = 0; i < roomArray.size(); i++){
				roomArray[i]->EditRoom(false);
				for (int j = 0; j < objectArray.size(); j++){
					if (objectArray[j]->Is("Wall")){
						objectArray[j]->Editing(false);
					}
				}
			}
			break;
		case GUI_A:
			if(gui.BuildIconPressed()){
				action = GUI_ROOM;
				gui.SetState(ROOMS);
            }
			else{
				if (gui.DestroyIconPressed()){
					action = DESTROY_ROOM;
				}
				else{
					if (gui.BuyIconPressed()){
						action = BUY;
					}
					else{
						if (gui.EditIconPressed()){
							subGuiEdit.SetPositionSubGUI(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
							action = SUB_GUI_EDIT;
							subGuiEdit.SetState(EDIT);
						}
						else {
							action = NONE;
						}
					}
				}
			}
			break;
		case SUB_GUI_EDIT:
			if (subGuiEdit.DoorIconPressed()){
				cout << "editando porta..." << endl;
				action = EDIT_DOOR;
			}
			else{
				if (subGuiEdit.WallIconPressed()){
					cout << "editando parede..." << endl;
					action = EDIT_WALL;
				}
				else {
					action = NONE;
				}
			}
			break;
		case TILE_SELECT:
			break;
		case GUI_ROOM:
			if (gui.PirateIconPressed()){
				rType = PIRATE;
				cout << "pirate" << endl;
				action = TILE_SELECT;
			}else{
				if (gui.SamuraiIconPressed()){
					rType = SAMURAI;
					cout << "Samurai" << endl;
					action = TILE_SELECT;
				}else{
					cout << "none" << endl;
					action = NONE;
				}

			}
			gui.SetState(BASIC);

			break;
		case CONSTRUCT_ROOM:
			{
			action = NONE;
			Point aux;

			if (selectionBox.begin.y > selectionBox.end.y) {
				aux = selectionBox.begin;
				selectionBox.begin = selectionBox.end;
				selectionBox.end = aux;
			}

			if ((selectionBox.begin.x > selectionBox.end.x) && (selectionBox.begin.y < selectionBox.end.y)) {
				aux = selectionBox.begin;
				selectionBox.begin.x = selectionBox.end.x;
				selectionBox.end.x = aux.x;
			}

			Room *newRoom = new Room(selectionBox.begin, selectionBox.end, &tileMap, &objectArray, roomArray.size(), rType);
            roomArray.emplace_back(newRoom);
			vector<int> heuristc = occupancyMap.CreateHeuristic(&tileMap, roomArray[roomArray.size() - 1]->GetDoor(), 0);
			heuristicsArray.emplace(newRoom->GetID(),heuristc);
			obstacleMap = occupancyMap.Update(&tileMap, &objectArray);
			//Point tileC = tileMap.GetTile(objectArray[0]->box.x + objectArray[0]->box.w / 2, objectArray[0]->box.y + objectArray[0]->box.h);
			//vector<int> path = PathAStar(tileC.x, tileC.y, newRoom->GetID());
			//objectArray[0]->AddObjective(path);
			}
			break;
		case DESTROY_ROOM:
			for (int i = 0; i < roomArray.size(); i++){
				p = tileMap.GetTile(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);
				if (roomArray[i]->IsInside(p)){
					heuristicsArray.erase(roomArray[i]->GetID());
					cout << "Destroying..." << endl;
					DestroyRoom(roomArray[i]->GetID());
					roomArray.erase(roomArray.begin() + i);
					i = roomArray.size();
				}
				
			}
			action = NONE;
			break;
		case BUY:
			data->money -= 100;
			action = NONE;
			break;
		case AREA_SELECT:
			break;
		case EDIT_DOOR:
			for (int i = 0; i < roomArray.size(); i++){
				p = tileMap.GetTile(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);
				if (roomArray[i]->IsInside(p)){
					cout << "editando quarto: " << roomArray[i]->GetID() << endl;
					roomArray[i]->EditRoom(true);
					for (int j = 0; j < objectArray.size(); j++){
						if (objectArray[j]->Is("Wall")){
							if ((p.x == objectArray[j]->tile.x) && (p.y == objectArray[j]->tile.y))
								roomArray[i]->SetDoor(p.x, p.y, roomArray[i]->GetID(), &objectArray);
						}
					}
					
					for (int j = 0; j < objectArray.size(); j++){
						if (objectArray[j]->Is("Wall")){
							if (objectArray[j]->roomID == roomArray[i]->GetID()) {
								objectArray[j]->Editing(true);
								if (objectArray[j]->tile.DisPoints(objectArray[j]->tile, roomArray[i]->GetDoor()) == 0) {
									objectArray.erase(objectArray.begin() + j); 
								}
							}
						}
					}
					vector<int> heuristc = occupancyMap.CreateHeuristic(&tileMap, roomArray[i]->GetDoor(), 0);
					heuristicsArray[roomArray[i]->GetID()] = heuristc;
					obstacleMap = occupancyMap.Update(&tileMap, &objectArray);
					obstacleMap = occupancyMap.CleanTile(&tileMap, roomArray[i]->GetDoor());
				}
			}
			action = NONE;
			break;
		case EDIT_WALL:
			for (int i = 0; i < roomArray.size(); i++){
				p = tileMap.GetTile(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);
				if (roomArray[i]->IsInside(p)){
					cout << "editando quarto: " << roomArray[i]->GetID() << endl;
					roomArray[i]->EditRoom(true);
					for (int j = 0; j < objectArray.size(); j++){
						if (objectArray[j]->Is("Wall")){
							if (objectArray[j]->roomID == roomArray[i]->GetID()) {
								objectArray[j]->Editing(true);
							}
						}
					}
				}
			}
			action = NONE;
			break;
		default:
			break;
		}

	}

	if(InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)){
		switch (action)
		{
		case NONE:
			gui.SetPosition(InputManager::GetInstance().GetMouseX(),InputManager::GetInstance().GetMouseY());
			action = GUI_A;
			break;
		case TILE_SELECT:
			break;
		case CONSTRUCT_ROOM:
			break;
		case DESTROY_ROOM:
			break;
		case AREA_SELECT:
			break;
		case GUI_A:
			gui.SetPosition(InputManager::GetInstance().GetMouseX(),InputManager::GetInstance().GetMouseY());			
			break;
		case SUB_GUI_EDIT:
			action = NONE;
			break;
		default:
			break;
		}
	}

	if(InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT)){

		switch (action){
		case NONE:
			break;
		case TILE_SELECT:
			action = CONSTRUCT_ROOM;
			break;
		case CONSTRUCT_ROOM:
			break;
		case DESTROY_ROOM:
			break;
		case AREA_SELECT:
			break;
		default:
			break;
		}

	}

	if(InputManager::GetInstance().MouseRelease(SDL_BUTTON_RIGHT)){

		switch (action){
		case NONE:
			//action = TILE_SELECT;
			break;
		case TILE_SELECT:
			break;
		case CONSTRUCT_ROOM:
			break;
		case DESTROY_ROOM:
			break;
		case AREA_SELECT:
			break;
		default:
			break;
		}

	}
	
}


void StageState::DestroyRoom(int roomID){
    cout << roomID << endl;
	Point pos;
    for(int i = 0; i<objectArray.size(); i++){
        if(objectArray[i]->roomID  == roomID){
			if (objectArray[i]->Type() == "LEFT_CORNER" || objectArray[i]->Type() == "RIGHT_CORNER"){
				if (objectArray[i]->Type() == "LEFT_CORNER"){
					pos.x = objectArray[i]->box.x;
					pos.y = objectArray[i]->box.y + objectArray[i]->box.h;

						pos = tileMap.GetTile(pos.x, pos.y);
					}
					else{
						pos.x = objectArray[i]->box.x + objectArray[i]->box.w;
						pos.y = objectArray[i]->box.y + objectArray[i]->box.h;

						pos = tileMap.GetTile(pos.x, pos.y);

					}
				}
			else{
				pos.x = objectArray[i]->box.x + objectArray[i]->box.w / 2;
				pos.y = objectArray[i]->box.y + objectArray[i]->box.h;
				pos = tileMap.GetTile(pos.x, pos.y);
			}
			occupancyMap.CleanTile(&tileMap, pos);
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

vector<int> StageState::PathAStar(int posX, int posY, int roomId){
	cout << "RoomID : " << roomId << endl;
	cout <<"Size : " <<roomArray.size() << endl;
	Point door = roomArray[roomId-1]->GetDoor();
	int index, cost, actualPos, movements = 0;
	Point posCost;
	bool arrived = false;
	priority_queue<Point, vector<Point>, CostComparator> costQueue;
	unordered_map<int, int> exploredTiles;
	unordered_map<int, int> allPaths;
	vector<int> heuristic = heuristicsArray[roomId];
	vector<int> path;

	index = posY*tileMap.GetWidth() + posX;
	if (door.x == posX && door.y == posY){
		path.emplace_back(index);
		return path;
	}
	actualPos = index;
	cost = heuristic[index];
	posCost.SetPoint(index, movements, cost);
	exploredTiles.emplace(index, -1);
	allPaths.emplace(actualPos, -1);
	costQueue.emplace(posCost);
	//cout << door.y*tileMap.GetWidth() + door.x << endl;
	//cout << "obs : " << obstacleMap[door.y*tileMap.GetWidth() + door.x] << endl;
	while (!arrived){
		costQueue.pop();
		movements++;
		//Explore sides
		//Up Right
		posY--;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
			allPaths.emplace(index, actualPos);
		}
		//Down Right
		posY++;
		posX++;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
			allPaths.emplace(index, actualPos);
		}
		//Down Left
		posY++;
		posX--;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
			allPaths.emplace(index, actualPos);
		}
		//Down Right
		posY--;
		posX--;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
			allPaths.emplace(index, actualPos);
		}

		//Get next tile

		posCost = costQueue.top();
		index = posCost.x;
		posY = (int)(index / tileMap.GetWidth());
		posX = index % tileMap.GetWidth();

		

		movements = posCost.y;
		if (posX == door.x && posY == door.y) {
			arrived = true;
			cout << "Achou : " << posX << "," << posY << endl;
			cout << "Movements : "<< movements << endl;
		}
		
		cost = posCost.z;
		exploredTiles.emplace(index, actualPos);
		actualPos = index;
		
	}
	path.emplace_back(index);
	while (allPaths[index] != -1){
		path.emplace_back(allPaths[index]);
		index = allPaths[index];
	}
	for (int i = path.size()-1; i >= 0; i--){
		//cout << "Path : " << (int)(path[i] / tileMap.GetWidth()) << "," << path[i] % tileMap.GetWidth() << endl;
	}
	return path;
}

void StageState::CreateCharacter(int x, int y){
	Point tile(x, y);
	tile = tileMap.GetTileCenter(tile);
	Permonkey* pM = new Permonkey(tile.x, tile.y, tile, tileMap);
	objectArray.emplace_back(pM);
}

void StageState::DestroyCharacter(int id){
	objectArray.erase(objectArray.begin() + id);
}