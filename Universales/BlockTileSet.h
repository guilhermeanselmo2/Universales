#ifndef BlockTileSetH
#define BlockTileSetH

#include "TileSet.h"
#include "Sprite.h"

class BlockTileSet : public TileSet {
private:
	Sprite tileSet;
	int rows;
	int columns;

public:
	BlockTileSet(int tileWidth, int tileHeight, string file);
	void Open(string file);
	void Render(unsigned int index, int x, int y);
};

#endif