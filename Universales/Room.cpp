#include "Room.h"
#include "Camera.h"
#include "Wall.h"

Room::Room(Point lBegin, Point lEnd, TileMap *tileMap, vector<unique_ptr<GameObject> > *objectArray, int RoomCount) : tileSp("img/tileset/tile_tatami.png"){
	Point tile;
    begin = lBegin;
    end = lEnd;
    string file;
    //door = Point(end.x, begin.y+2);
    RoomID = RoomCount+1;

    file = "img/wall_corner_upper.png";
    Point pos(begin.x,begin.y);
	tile = pos;
    pos = tileMap->GetTileCenter(pos);
    //cout << begin.x << "," << begin.y << endl;
    Wall *wall = new Wall(pos.x, pos.y+tileMap->GetTileHeight()/4, file, UPPER_CORNER, tile, RoomID);
    objectArray->emplace_back(wall);

    file = "img/wall_corner_left.png";
    pos.SetPoint(begin.x,end.y);
	tile = pos;
    pos = tileMap->GetTileCenter(pos);
	wall = new Wall(pos.x + tileMap->GetTileWidth() / 4, pos.y + tileMap->GetTileHeight() / 4, file, LEFT_CORNER, tile, RoomID);
    objectArray->emplace_back(wall);

    file = "img/wall_corner_right.png";
    pos.SetPoint(end.x,begin.y);
	tile = pos;
    pos = tileMap->GetTileCenter(pos);
	wall = new Wall(pos.x - tileMap->GetTileWidth() / 4, pos.y + tileMap->GetTileHeight() / 4, file, RIGHT_CORNER, tile, RoomID);
    objectArray->emplace_back(wall);

    file = "img/wall_corner_lower.png";
    pos.SetPoint(end.x,end.y);
	tile = pos;
    pos = tileMap->GetTileCenter(pos);
	wall = new Wall(pos.x, pos.y, file, UPPER_CORNER, tile, RoomID);
    objectArray->emplace_back(wall);


    file = "img/wall_2.png";
    for(int i = begin.x+1; i< end.x; i++){
        Point pos(i,begin.y);
		tile = pos;
        if(i != door.x || pos.y != door.y){
            pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 4, pos.y + tileMap->GetTileHeight() / 4, file, UPPER_RIGHT, tile, RoomID);
            objectArray->emplace_back(wall);
        }

        if(i != door.x || pos.y != door.y){
            pos.SetPoint(i,end.y);
			tile = pos;
            pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 4, pos.y + tileMap->GetTileHeight() / 4, file, UPPER_RIGHT, tile, RoomID);
            objectArray->emplace_back(wall);
        }
    }
    /*for(int i = begin.x+1; i< end.x; i++){
        Point pos(i,begin.y-1);
        pos = tileMap->GetTileCenter(pos);
        Wall *wall = new Wall(pos.x-tileMap->GetTileWidth()/4, pos.y+tileMap->GetTileHeigh()/4, file, UPPER_RIGHT);
        objectArray->emplace_back(wall);
    }*/
    file = "img/wall_1.png";
    for(int i = begin.y+1; i< end.y; i++){
        Point pos(begin.x,i);
		tile = pos;
        if(i != door.x || pos.y != door.y){
            pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 4, pos.y + tileMap->GetTileHeight() / 4, file, UPPER_LEFT, tile, RoomID);
            objectArray->emplace_back(wall);
        }

        pos.SetPoint(end.x,i);
		tile = pos;
        if(((pos.x   != door.x) || (pos.y != door.y))){
            pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 4, pos.y + tileMap->GetTileHeight() / 4, file, UPPER_LEFT, tile, RoomID);
            objectArray->emplace_back(wall);
        }

    }

}

void Room::EditRoom(bool editing) {
	if (editing)
		roomState = EDITING;
	else
		roomState = NONE;
}

void Room::Render(TileMap *tileMap){
	editTimer.Update(Game::GetInstance().GetDeltaTime());
	if (roomState == EDITING) {
		if (editTimer.Get() < 1.0){
			Point renderPos;
			if (end.x < begin.x){
				if (end.y < begin.y){
					for (int i = end.x; i <= begin.x; i++){
						for (int j = end.y; j <= begin.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
				else{
					for (int i = end.x; i <= begin.x; i++){
						for (int j = begin.y; j <= end.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
			}
			else{
				if (end.y < begin.y){
					for (int i = begin.x; i <= end.x; i++){
						for (int j = end.y; j <= begin.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
				else{
					for (int i = begin.x; i <= end.x; i++){
						for (int j = begin.y; j <= end.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
			}
		}
		if (editTimer.Get() > 1.5)
			editTimer.Restart();
	}
	else {
		Point renderPos;
		if (end.x < begin.x){
			if (end.y < begin.y){
				for (int i = end.x; i <= begin.x; i++){
					for (int j = end.y; j <= begin.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
			else{
				for (int i = end.x; i <= begin.x; i++){
					for (int j = begin.y; j <= end.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
		}
		else{
			if (end.y < begin.y){
				for (int i = begin.x; i <= end.x; i++){
					for (int j = end.y; j <= begin.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
			else{
				for (int i = begin.x; i <= end.x; i++){
					for (int j = begin.y; j <= end.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
		}
	}
}

bool Room::IsInside(float x, float y){
    if(begin.x <= x <= end.x && begin.y <= y <= end.y){
        return true;
    }
    return false;

}

bool Room::IsInside(Point tile){
    if(begin.x <= tile.x && tile.x <= end.x && (begin.y <= tile.y) && tile.y <= end.y){
        return true;
    }
    return false;
}

int Room::GetID(){
    return RoomID;
}

Point Room::GetDoor(){
	return door;
}
