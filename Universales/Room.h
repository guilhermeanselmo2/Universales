#ifndef ROOM_H
#define ROOM_H

#include "SelectionBox.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Timer.h"
#include <vector>
#include <memory>

enum RoomType{
	CORRIDOR = 0,
	SAMURAI,
	PIRATE,
	STEAM,
};

struct RoomAttributes{
	string type;
	int cost;
	string tileSprite;
	string description;
};

class Room{
public:
	enum RoomState{
		NONE = 0,
		EDITING
	};
	Room(Point lBegin, Point lEnd, TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray, int roomCount, RoomAttributes attributes);
	Room(ifstream &readFile, TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray, int RoomCount);
    void Update(float dt);
    void Render(TileMap *tileMap);
	void EditRoom(bool editing);
    int GetID();
	string GetState();
    bool IsInside(float x, float y);
    bool IsInside(Point tile);
    bool Is(string type);
	void SetEnd(Point end);
	void DeleteTileWall(Point p, int RoomID, vector<unique_ptr<GameObject>> *objectArray);
	void InsertTileWall(Point p, int RoomID, vector<unique_ptr<GameObject>> *objectArray);
	void SetBegin(Point begin);
	Point GetTileCenterRoom();
	Point GetBegin();
	Point GetEnd();
	void SetDoor(float x, float y, int RoomID, vector<unique_ptr<GameObject>> *objectArray);
	RoomState roomState;
	Point GetDoor();
	Timer editTimer;
	int cost;
	void Save(ofstream &file);

private:
	TileMap tileMap;
    vector<vector<Point>> tiles;
    Sprite tileSp;
    Point begin;
    Point end;
    Point door;
    int RoomID;
	RoomAttributes attributes;
    SelectionBox floor;
    vector<unique_ptr<GameObject>> wallArray;
};

#endif // ROOM_H
