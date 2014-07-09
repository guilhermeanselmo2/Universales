#ifndef ROOM_H
#define ROOM_H

#include "SelectionBox.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Timer.h"
#include <vector>
#include <memory>

class Room{
public:
	enum RoomState{
		NONE = 0,
		EDITING
	};
    Room(Point lBegin, Point lEnd, TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray, int roomCount);
    void Update(float dt);
    void Render(TileMap *tileMap);
	void EditRoom(bool editing);
    int GetID();
    bool IsInside(float x, float y);
    bool IsInside(Point tile);
    bool Is(string type);
<<<<<<< Temporary merge branch 1
	RoomState roomState;
	Timer editTimer;
=======
	Point GetDoor();
>>>>>>> Temporary merge branch 2

private:
    vector<vector<Point>> tiles;
    Sprite tileSp;
    Point begin;
    Point end;
    Point door;
    int RoomID;
    SelectionBox floor;
    vector<unique_ptr<GameObject>> wallArray;
};

#endif // ROOM_H
