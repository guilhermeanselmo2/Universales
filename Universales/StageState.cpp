#include "StageState.h"
#include "EndState.h"
#include "Alien.h"
#include "Penguins.h"
#include "Music.h"
#include "StateData.h"
#include "Permonkey.h"
#include "CostComparator.h"


StageState::StageState() : tileSet(152,76), tileMap("map/tileMap.txt", &tileSet),
	moneyText("font/enhanced_dot_digital-7.ttf", 40, Text::TEXT_BLENDED, "-", WHITE, 100), occupancyMap(tileMap.GetWidth(), tileMap.GetWidth()){
	string file, tile, line, endLine("\n"), initFile("img/tileset/");
	FILE *tileFile;
	char c;

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

	Point monkeyTile(0,0);
	Point teste(0, 0);
    monkeyTile = tileMap.GetTileCenter(monkeyTile);
    Permonkey* pM = new Permonkey(monkeyTile.x, monkeyTile.y, teste, tileMap);
    objectArray.emplace_back(pM);

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
	
	Point teste = tileMap.GetTile(objectArray[0]->box.x + objectArray[0]->box.w / 2, objectArray[0]->box.y + objectArray[0]->box.h);
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
		break;
	case TILE_SELECT:
		selectionBox.Render(&tileMap);
		RenderArray();
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
				action = TILE_SELECT;
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
							action = EDIT_ROOM;
						}
						else {
							action = NONE;
						}
					}
				}
			}
			break;
		case TILE_SELECT:
			break;
		case CONSTRUCT_ROOM:
			{
			action = NONE;
			Room *newRoom = new Room(selectionBox.begin, selectionBox.end, &tileMap, &objectArray, roomArray.size());
            roomArray.emplace_back(newRoom);
			vector<int> heuristc = occupancyMap.CreateHeuristic(&tileMap, roomArray[roomArray.size() - 1]->GetDoor(), 0);
			heuristicsArray.emplace(newRoom->GetID(),heuristc);
			obstacleMap = occupancyMap.Update(&tileMap, &objectArray);
			Point tileC = tileMap.GetTile(objectArray[0]->box.x + objectArray[0]->box.w / 2, objectArray[0]->box.y + objectArray[0]->box.h);
			PathAStar(tileC.x, tileC.y, newRoom->GetID());
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

			// Isso aki não é aki não =D

			/* for (int i = 0; i < roomArray.size(); i++){
				p = tileMap.GetTile(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
				if (roomArray[i]->IsInside(p)){
					cout << "Destroying..." << endl;
					DestroyRoom(roomArray[i]->GetID());
					roomArray.erase(roomArray.begin() + i);
					i = roomArray.size();
				}
			} */
			data->money -= 100;
			action = NONE;
			break;
		case AREA_SELECT:
			break;
		case EDIT_ROOM:
			
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
		case EDIT_ROOM:
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
		case EDIT_ROOM:
			break;
		default:
			break;
		}

	}

	if(InputManager::GetInstance().MouseRelease(SDL_BUTTON_RIGHT)){

		switch (action){
		case NONE:
			action = TILE_SELECT;
			break;
		case TILE_SELECT:
			break;
		case CONSTRUCT_ROOM:
			break;
		case DESTROY_ROOM:
			break;
		case AREA_SELECT:
			break;
		case EDIT_ROOM:
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

void StageState::PathAStar(int posX, int posY, int roomId){
	cout << "RoomID : " << roomId << endl;
	cout <<"Size : " <<roomArray.size() << endl;
	Point door = roomArray[roomId-1]->GetDoor();
	door.x = 7;
	door.y = 7;
	int index, cost, actualPos, movements = 0;
	Point posCost;
	bool arrived = false;
	priority_queue<Point, vector<Point>, CostComparator> costQueue;
	unordered_map<int, int> exploredTiles;
	vector<int> heuristic = heuristicsArray[roomId];

	if (door.x == posX && door.y == posY){
		return;
	}
	index = posY*tileMap.GetWidth() + posX;
	actualPos = index;
	cost = heuristic[index];
	posCost.SetPoint(index, movements, cost);
	exploredTiles.emplace(index, cost);
	costQueue.emplace(posCost);
	
	while (!arrived){
		int a;
		cin >> a;
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
		}
		//Down Right
		posY++;
		posX++;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
		}
		//Down Left
		posY++;
		posX--;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
		}
		//Down Right
		posY--;
		posX--;
		index = posY*tileMap.GetWidth() + posX;
		if (exploredTiles.find(index) == exploredTiles.end() && posX >= 0 && posY >= 0 && obstacleMap[index] != -1){
			cost = heuristic[index] + movements;
			posCost.SetPoint(index, movements, cost);
			costQueue.emplace(posCost);
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
		exploredTiles.emplace(index, cost);
	}
}