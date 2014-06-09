#include "TileMap.h"

using namespace std;

TileMap::TileMap() {}

TileMap::TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet) : mapWidth(mapWidth), mapHeight(mapHeight), mapDepth(layers), tileSet(tileSet) {
	tileMatrix.resize(mapWidth*mapHeight*mapDepth, -1);
}

TileMap::TileMap(string file, TileSet* tileSet) : tileSet(tileSet) {
	Load(file);
}

void TileMap::Load(string file) {
	int numero, i = 0;
	FILE *fp = fopen(file.c_str(), "r");
	if (fp == NULL) {
		std::cout << "Mapa nao carregado ..." << std::endl;
		exit(1);
	}
	fscanf(fp, "%d%*c", &numero);
	mapWidth = numero;
	fscanf(fp, "%d%*c", &numero);
	mapHeight = numero;
	fscanf(fp, "%d%*c", &numero);
	mapDepth = numero;

	tileMatrix.resize(mapWidth*mapHeight*mapDepth, -1);

	while (!feof(fp)) {
		fscanf(fp, "%d%*c", &numero);
		tileMatrix[i] = (numero-1);
		i++;
	}

	fclose(fp);
	
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	return tileMatrix[(y*mapWidth) + x + (z*mapHeight*mapWidth)];
}

Point TileMap::GetTile(int screenX, int screenY, int layer){
    float side = sqrt(pow(-4+tileSet->GetTileWidth()/2,2)+pow(-2+tileSet->GetTileHeight()/2,2));
    Point object(screenX-512,screenY);
    float objMag = sqrt(object.x*object.x + object.y*object.y);
    float tileThetaR = atan2(tileSet->GetTileHeight()/2,tileSet->GetTileWidth()/2);
    float tileThetaL = M_PI-tileThetaR;
    float thetaR = atan2(object.y,object.x)-tileThetaR;
    float thetaL = tileThetaL - atan2(object.y,object.x);
    int r, l;

    //Check if it is off the tile map, if it is, returns a negative position


    r = int ((objMag*sin(M_PI-thetaR-2*tileThetaR)/sin(2*tileThetaR))/side);

    l = int ((objMag*sin(M_PI-thetaL-2*tileThetaR)/sin(2*tileThetaR))/side);

    Point p(r,l);
    return p;
}

Point TileMap::GetTileCenter(Point tile, int layer){
    float x0, y0, x, y;
    x0 = 512;
    y0 = tileSet->GetTileHeight()/2;
    x = x0 - tile.y*(-4+tileSet->GetTileWidth()/2) + tile.x*(tileSet->GetTileWidth()/2-4);
    y = y0 + tile.y*(-2+tileSet->GetTileHeight()/2) + tile.x*(tileSet->GetTileHeight()/2-2);
    Point p(x,y);
    return p;
}

Point TileMap::GetTileCenterFromScreen(Point pos, int layer){
    Point tile;
    tile = GetTile(pos.x, pos.y, layer);
    return GetTileCenter(tile, layer);
}

void TileMap::Render(int cameraX, int cameraY) {
	for (int i = 0; i<mapDepth; i++) {
			RenderLayer(i, (cameraX + cameraX*i), (cameraY + cameraY*i));
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int x0, y0, x, y;
    y0 = tileSet->GetTileHeight()/2;
    x0 = 512;
    for(int j =  0; j<mapHeight;j++){
        x = x0-j*(-4+tileSet->GetTileWidth()/2);
        y = y0+j*(-2+tileSet->GetTileHeight()/2);
        for(int i = 0; i<mapWidth;i++){
            tileSet->Render(tileMatrix[i+j*mapWidth+layer*mapHeight*mapWidth], x+cameraX*(layer+1), y+cameraY*(layer+1));
            x = x + tileSet->GetTileWidth()/2-4;
            y = y + tileSet->GetTileHeight()/2-2;
        }
    }
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

int TileMap::GetTileWidth(){
    return tileSet->GetTileWidth();
}

int TileMap::GetTileHeight(){
    return tileSet->GetTileHeight();
}