#include "MultiTileSet.h"

MultiTileSet::MultiTileSet() {}

MultiTileSet::MultiTileSet(int tileWidth, int tileHeight) {
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;
}

MultiTileSet::~MultiTileSet() {
	tileArray.clear();
}

void MultiTileSet::Open(string file) {
	Sprite sprite(file);
	tileArray.emplace_back(sprite);
}

void MultiTileSet::Render(unsigned int index, int x, int y) {
	if ((index >= 0) && (index < tileArray.size()))
		tileArray[index].Render(x-tileWidth/2, y-tileHeight/2);
}

