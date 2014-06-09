#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "Sprite.h"

enum WallStyle{
        UPPER_RIGHT = 0,
        UPPER_LEFT,
        LOWER_RIGHT,
        LOWER_LEFT,
    UPPER_CORNER,
    LEFT_CORNER,
    RIGHT_CORNER,
    INF_CORNER,
};


class Wall : public GameObject{
public:
    Wall(float centerX, float centerY, string file, WallStyle lStyle, int lRoom = 0);
    ~Wall();

    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(string type);
    string Type();
	void AddObjective(float x, float y);

private:
    Sprite wall;
    WallStyle style;

};

#endif //WALL_H
