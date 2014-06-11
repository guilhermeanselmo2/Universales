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
#include "PauseState.h"
#include "CheatState.h"
#include "Text.h"
#include "Object.h"

enum Action{

	NONE = 0,
	TILE_SELECT,
	CONSTRUCT_ROOM,
	DESTROY_ROOM,
	AREA_SELECT,
	GUI_A,
	SUB_GUI_EDIT,
	BUY,
	EDIT_ROOM,
	EDIT_WALL,
	EDIT_DOOR,
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
	Point ptile;
	vector<unique_ptr<Room>> roomArray;
	vector<unique_ptr<Character>> characterArray;
	GUI gui;
	//GUI subGuiEdit;
	Text moneyText;
};

#endif