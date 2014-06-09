#ifndef MultiTileSetH
#define MultiTileSetH

#include "TileSet.h"
#include "Sprite.h"

class MultiTileSet : public TileSet {
protected:
	std::vector<Sprite> tileArray;
public:
	MultiTileSet();
	MultiTileSet(int width, int height);
	~MultiTileSet();
	void Open(string file);
	void Render(unsigned int index, int x, int y);
};

#endif