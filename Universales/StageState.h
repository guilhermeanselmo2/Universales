#ifndef StageStateH
#define StageStateH

#include "Wall.h"
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
#include "Timer.h"
#include "Object.h"
#include "OccupancyMap.h"
#include "Permonkey.h"
#include "CharacterSheet.h"
#include "Object.h"
#include "Sheet.h"

enum Action{

	NONE = 0,
	TILE_SELECT,
	GUI_ROOM,
	CONSTRUCT_ROOM,
	DESTROY_ROOM,
	AREA_SELECT,
	GUI_A,
	GUI_EDIT,
	EXPAND_WALL,
	GUI_WALL,
	BUY,
	MOVE_WALL,
	EDIT_DOOR,
	SELECT_ROOM,
	SELECT_WALL,
	EDIT_OBJECT
};

class StageState : public State {
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void DestroyRoom(int roomID);
	void CreateCharacter(int x, int y);
	void DestroyCharacter(int id);
	vector<int> PathAStar(int posX, int posY, int roomId);
	void SelectCharacter();
	void CreateStationWalls(Point begin,Point end,TileMap *tileMap, vector<unique_ptr<GameObject> > *objectArray);

private:
	void Input();
	void ParseObject(vector<string> objList);
	Sprite bg;
	MultiTileSet tileSet;
	TileMap tileMap;
	Action action;
	SelectionBox selectionBox;
	Point p;
	Point move;
	Point selectedWall;
	Point tileBegin;
	Point tileEnd;
	Point ptile;
	RoomType rType;
	RoomType charRoom;
	vector<unique_ptr<Room>> roomArray;
	vector<int> obstacleMap;
	unordered_map<int, vector<int>> heuristicsArray;
	
	Timer creationTimer;
	GUI gui;
	Text moneyText;
	OccupancyMap occupancyMap;
	Choice charChoice;
	CharacterSheet sheet;
	Sheet buySheet;
	int selectedObject;
	int selectedRoom;
};

#endif