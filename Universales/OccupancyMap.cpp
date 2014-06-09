#include "OccupancyMap.h"


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

