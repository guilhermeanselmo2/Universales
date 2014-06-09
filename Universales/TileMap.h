#ifndef TileMapH
#define TileMapH

#include "TileSet.h"
#include "Camera.h"

class TileMap {
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
public:
	TileMap();
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