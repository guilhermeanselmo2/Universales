#ifndef TileSetH
#define TileSetH

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;

class TileSet {
protected:
	int tileWidth;
	int tileHeight;

public:
	virtual ~TileSet();
	virtual void Open(string file) = 0;
	virtual void Render(unsigned int index, int x, int y) = 0;
	int GetTileWidth();
	int GetTileHeight();
};


#endif