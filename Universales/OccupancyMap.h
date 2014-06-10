#ifndef OccupancyMapH
#define OccupancyMapH

#include <vector>
#include <memory>
#include "TileMap.h"

using namespace std;

class OccupancyMap{
public:
	OccupancyMap(int x, int y);
	~OccupancyMap();
	void Update(TileMap *tileMap, vector<unique_ptr<GameObject>> objectArray);
	void CreateHeuristic(TileMap *tileMap, Point door, int RoomID);
	void Render(TileMap *tileMap);

	vector<int> occupancyMap;

private:
	vector<int> heuristics;
};


#endif

