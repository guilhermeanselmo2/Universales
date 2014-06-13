#include "OccupancyMap.h"
#include "Text.h"
#include "Camera.h"


OccupancyMap::OccupancyMap(int x, int y) : sp("img/flor_amarela_1.png"){
	occupancyMap.resize(x*y, 0);
}


OccupancyMap::~OccupancyMap()
{
}

vector<int> OccupancyMap::Update(TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray){
	Point pos;
	int index;
	occupancyMap.resize(occupancyMap.size(), 0);
	for (int i = 0; i < objectArray->size(); i++){
		if (!(objectArray->at(i)->Is("PerMonkey"))){

			if (objectArray->at(i)->Type() == "LEFT_CORNER" || objectArray->at(i)->Type() == "RIGHT_CORNER"){
				if (objectArray->at(i)->Type() == "LEFT_CORNER"){
					pos.x = objectArray->at(i)->box.x;
					pos.y = objectArray->at(i)->box.y + objectArray->at(i)->box.h;
					
					pos = tileMap->GetTile(pos.x, pos.y);
					index = pos.y*tileMap->GetHeight() + pos.x;
					occupancyMap[index] = -1;
				}
				else{
					pos.x = objectArray->at(i)->box.x + objectArray->at(i)->box.w;
					pos.y = objectArray->at(i)->box.y + objectArray->at(i)->box.h;
					
					pos = tileMap->GetTile(pos.x, pos.y);
					index = pos.y*tileMap->GetHeight() + pos.x;
					occupancyMap[index] = -1;

				}
			}
			else{
				pos.x = objectArray->at(i)->box.x + objectArray->at(i)->box.w / 2;
				pos.y = objectArray->at(i)->box.y + objectArray->at(i)->box.h;
				pos = tileMap->GetTile(pos.x, pos.y);

				index = pos.y*tileMap->GetHeight() + pos.x;
				occupancyMap[index] = -1;
			}
		}
	}
	return occupancyMap;
}

vector<int> OccupancyMap::CreateHeuristic(TileMap *tileMap, Point door, int RoomID){
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
	return heuristic;
}


//Debug only! Very heavy! Caused my game to crash! Don't use it!
void OccupancyMap::Render(TileMap *tileMap){ 
	Text text("font/LCALLIG.TTF", 40, Text::TEXT_BLENDED, "  ", WHITE, 100);
	int x, y;/*
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
	
	for (int i = 0; i < occupancyMap.size(); i++){
		x = i%tileMap->GetWidth();
		y = (int)(i / tileMap->GetWidth());

		Point pos(x, y);
		Point p = tileMap->GetTileCenter(pos);
		if (occupancyMap[i] == -1){
			sp.Render(p.x - sp.GetWidth() / 2, p.y - sp.GetHeight() / 2);
		}
	} */
}

vector<int> OccupancyMap::CleanTile(TileMap *tileMap, Point tile){
	int index = tile.y*tileMap->GetWidth() + tile.x;
	occupancyMap[index] = 0;
	cout << index << endl;
	return occupancyMap;
}



