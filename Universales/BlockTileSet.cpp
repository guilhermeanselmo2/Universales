#include "BlockTileSet.h"

BlockTileSet::BlockTileSet(int tileWidth, int tileHeight, string file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	Open(file);
}

void BlockTileSet::Open(string file) {
	tileSet.Open(file);
	columns = tileSet.GetWidth()/tileWidth;
	rows = tileSet.GetHeight()/tileHeight;
}

void BlockTileSet::Render(unsigned int index, int x , int y){
	int numHeight;
	int numWidth;
	if ((index >= 0) && (index < columns*rows))
		numHeight = index / columns;
		numWidth = index%columns;
		tileSet.SetClip(numWidth*tileWidth, numHeight*tileHeight, tileWidth, tileHeight);
		tileSet.Render(x, y);
}