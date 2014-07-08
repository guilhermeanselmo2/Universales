#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Point.h"

enum WallStyle{
    UPPER_RIGHT = 0,
    UPPER_LEFT,
    LOWER_RIGHT,
    LOWER_LEFT,
    UPPER_CORNER,
    LEFT_CORNER,
    RIGHT_CORNER,
	STATION_WALL,
    INF_CORNER,
};


class Wall : public GameObject{
public:
	Wall(float centerX, float centerY, string file, WallStyle lStyle, Point lTile, TileMap *tileMap, int lRoom = 0);
    ~Wall();

    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(string type);
	bool IsCharacter();
	void Editing(bool editing);
    string Type();
	void AddObjective(float x, float y, Point tile);
	void AddObjective(vector<int> path);
	Choice GetChoice();
	int GetHunger();
	void MoveTo(int x, int y);
private:
	TileMap tileMap;
	Timer editTimer;
	bool editing;
    Sprite wall;
    WallStyle style;

};

#endif //WALL_H
