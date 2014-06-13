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
#include "OccupancyMap.h"

enum Action{

	NONE = 0,
	TILE_SELECT,
	CONSTRUCT_ROOM,
	DESTROY_ROOM,
	AREA_SELECT,
	GUI_A,
	SUB_GUI_EDIT,
	BUY,
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
	vector<int> PathAStar(int posX, int posY, int roomId);

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
	vector<int> obstacleMap;
	unordered_map<int, vector<int>> heuristicsArray;
	
	GUI gui;
	GUI subGuiEdit;
	Text moneyText;
	OccupancyMap occupancyMap;
};

#endif