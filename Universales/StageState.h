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
#include "Timer.h"
#include "Object.h"
#include "OccupancyMap.h"
#include "Permonkey.h"
#include "CharacterSheet.h"
#include "Object.h"
#include "Sheet.h"
#include "Music.h"

enum Action{

	NONE = 0,
	TILE_SELECT,
	GUI_ROOM,
	CONSTRUCT_ROOM,
	DESTROY_ROOM,
	AREA_SELECT,
	GUI_A,
	SUB_GUI_EDIT,
	BUY,
	EDIT_WALL,
	EDIT_DOOR,
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
	void Load();
	void Save();
	static StageState *instance;
	Music music;
	int cMusic;
	Sound click;

private:
	void Input();
	void ParseObject(vector<string> objList);
	Sprite bg;
	MultiTileSet tileSet;
	TileMap tileMap;
	Action action;
	SelectionBox selectionBox;
	Point p;
	Point ptile;
	RoomType rType;
	RoomType charRoom;
	vector<unique_ptr<Room>> roomArray;
	vector<int> obstacleMap;
	unordered_map<int, vector<int>> heuristicsArray;
	
	Timer creationTimer;
	GUI gui;
	GUI subGuiEdit;
	Text moneyText;
	Text costText;
	OccupancyMap occupancyMap;
	Choice charChoice;
	CharacterSheet sheet;
	Sheet buySheet;
	int selectedObject;

	static vector<string> musicNames;
};

#endif