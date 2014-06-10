#include "OccupancyMap.h"
#include "Text.h"
#include "Camera.h"


OccupancyMap::OccupancyMap(int x, int y){
	occupancyMap.resize(x*y, 0);
}


OccupancyMap::~OccupancyMap()
{
}

void OccupancyMap::Update(TileMap *tileMap, vector<unique_ptr<GameObject>> objectArray){
	for (int i = 0; i < objectArray.size(); i++){
		if (!(objectArray[i]->Is("Permonkey"))){
			//objectArray[i]->box;
		}
	}
}

void OccupancyMap::CreateHeuristic(TileMap *tileMap, Point door, int RoomID){
	vector<int> heuristic;
	int distX, distY;
	heuristic.resize(occupancyMap.size());
	heuristics.resize(occupancyMap.size());
	for (int i = 0; i < heuristic.size(); i++){
		distX = i%tileMap->GetWidth() - door.x;
		distY = ((int)(i / tileMap->GetWidth())) - door.y;
		heuristic[i] = abs(distX) + abs(distY);
		heuristics[i] = heuristic[i];
	}
}


//Debug only! Very heavy! Caused my game to crash! Don't use it!
void OccupancyMap::Render(TileMap *tileMap){
	Text text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "  ", WHITE, 100);
	int x, y;
	for (int i = 0; i < heuristics.size(); i++){
		string h = to_string(heuristics[i]);
		text.SetText(h);
		x = i%tileMap->GetWidth();
		y = (int)(i / tileMap->GetWidth());
		
		Point pos(x, y);
		Point p = tileMap->GetTileCenter(pos);
		text.SetPos(p.x,p.y,true,true);
		text.Render(-Camera::pos.x, -Camera::pos.y);
	}
}



