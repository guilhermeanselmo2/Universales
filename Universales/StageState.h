#ifndef StageStateH
#define StageStateH

#include "State.h"
#include "Sprite.h"
#include "BlockTileSet.h"
#include "MultiTileSet.h"
#include "TileMap.h"
#include "SelectionBox.h"
#include "Room.h"
#include "Character.h"
#include "GUI.h"

enum Action{

    NONE = 0,
    TILE_SELECT,
    CONSTRUCT_ROOM,
    DESTROY_ROOM,
    AREA_SELECT,
	GUI_A,
};

class StageState : public State {
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void DestroyRoom(int roomID);
private:
	void Input();
	Sprite bg;
	MultiTileSet tileSet;
	TileMap tileMap;
	Action action;
	SelectionBox selectionBox;
	Point p;
	vector<unique_ptr<Room>> roomArray;
	vector<unique_ptr<Character>> characterArray;
	GUI gui;
};

#endif