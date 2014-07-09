#ifndef TileMapH
#define TileMapH

#if _MSC_VER > 1020   // if VC++ version is > 4.2
using namespace std;  // std c++ libs implemented in std
#endif

#include "TileSet.h"
#include "Camera.h"

class TileMap {
private:
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	int tileMatrix[625];
public:
	TileMap();
	~TileMap();
	TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet = NULL);
	TileMap(string file, TileSet* tileSet = NULL);
	void Load(string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z = 0);
	Point GetTile(int screenX, int screenY, int layer=0);
    Point GetTileCenter(Point tile, int layer=0);
    Point GetTileCenterFromScreen(Point pos, int layer = 0);
	void Render(int cameraX = 0, int cameraY = 0);
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	int GetTileWidth();
	int GetTileHeight();

};

#endif