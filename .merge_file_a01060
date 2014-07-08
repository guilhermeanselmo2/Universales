#ifndef ROOM_H
#define ROOM_H

#include "SelectionBox.h"
#include "GameObject.h"
#include "TileMap.h"
#include <vector>
#include <memory>

class Room{
public:
    Room(Point lBegin, Point lEnd, TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray, int roomCount);
    void Update(float dt);
    void Render(TileMap *tileMap);
    int GetID();
    bool IsInside(float x, float y);
    bool IsInside(Point tile);
    bool Is(string type);

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
