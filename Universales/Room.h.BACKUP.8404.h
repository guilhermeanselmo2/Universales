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

class Room{
public:
	enum RoomState{
		NONE = 0,
		EDITING
	};
    Room(Point lBegin, Point lEnd, TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray, int roomCount, RoomType type);
    void Render(TileMap *tileMap);
	void EditRoom(bool editing);
    int GetID();
	RoomType GetState();
    bool IsInside(float x, float y);
    bool IsInside(Point tile);
    bool Is(string type);
<<<<<<< HEAD
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
	vector<unique_ptr<GameObject>> wall1Array, wall2Array;
=======
    Point GetDoor();
    RoomState roomState;
    Timer editTimer;
>>>>>>> Uruainstein-master

private:
	TileMap tileMap;
    vector<vector<Point>> tiles;
    Sprite tileSp;
    Point begin;
    Point end;
    Point door;
    int RoomID;
	RoomType roomType;
    SelectionBox floor;
    
};

#endif // ROOM_H
