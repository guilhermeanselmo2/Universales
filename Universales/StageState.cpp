#include "StageState.h"
#include "EndState.h"
#include "Alien.h"
#include "Penguins.h"
#include "Music.h"
#include "StateData.h"
#include "Permonkey.h"

StageState::StageState() : tileSet(152,76), tileMap("map/tileMap.txt", &tileSet) {
	string file, tile, line, endLine("\n"), initFile("img/tileset/");
	FILE *tileFile;
	char c;

	action = NONE;

	bg.Open("img/ocean.jpg");
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

	Point monkeyTile(5,5);
    monkeyTile = tileMap.GetTileCenter(monkeyTile);
    Permonkey* pM = new Permonkey(monkeyTile.x, monkeyTile.y);
    objectArray.emplace_back(pM);
	//characterArray.emplace_back(pM);

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

}

StageState::~StageState() {
	objectArray.clear();
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
}

void StageState::Render() {
	bg.Render(0, 0);
	tileMap.Render(Camera::pos.GetXpoint(), Camera::pos.GetYpoint());
	
	for(int i = 0; i < roomArray.size(); i++){
        roomArray[i]->Render(&tileMap);
    }
	switch (action)	{
	case NONE:
		break;
	case TILE_SELECT:
		selectionBox.Render(&tileMap);
		break;
	case CONSTRUCT_ROOM:
		selectionBox.Render(&tileMap);
		break;
	case DESTROY_ROOM:
		break;
	case AREA_SELECT:
		break;
	case GUI_A:
		gui.Render();
		break;
	default:
		break;
	}
	RenderArray();
}

void StageState::Input() {
	if ((InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) || (InputManager::GetInstance().ShouldQuit())){
		requestQuit = true;
	}

	if(InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){

		switch (action){
		case NONE:
			p = tileMap.GetTile(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
            p = tileMap.GetTileCenter(p);
			objectArray[0]->AddObjective(p.x, p.y);
			break;
		case GUI_A:
			if(gui.BuildIconPressed()){
				action = TILE_SELECT;
            }
            if(gui.DestroyIconPressed()){
				action = DESTROY_ROOM;
            }
			break;
		case TILE_SELECT:
			break;
		case CONSTRUCT_ROOM:
			{
			action = NONE;
			Room *newRoom = new Room(selectionBox.begin, selectionBox.end, &tileMap, &objectArray, roomArray.size());
            roomArray.emplace_back(newRoom);
			}
			break;
		case DESTROY_ROOM:
			for(int i = 0; i < roomArray.size(); i++){
                p = tileMap.GetTile(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
                if(roomArray[i]->IsInside(p)){
                    cout << "Destroying..." << endl;
                    DestroyRoom(i+1);
					roomArray.erase(roomArray.begin()+i);
					i = roomArray.size();
				}
            }
			action = NONE;
			break;
		case AREA_SELECT:
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
		default:
			break;
		}

	}
	
}


void StageState::DestroyRoom(int roomID){
    cout << roomID << endl;
    for(int i = 0; i<objectArray.size(); i++){
        if(objectArray[i]->roomID  == roomID){
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}