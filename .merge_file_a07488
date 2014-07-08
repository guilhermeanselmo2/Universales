#ifndef PERMONKEY_H
#define PERMONKEY_H

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Character.h"
#include "GameObject.h"
#include <queue>

class Permonkey : public GameObject{
public:
    Permonkey(float x, float y);
    ~Permonkey();
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision (GameObject& other);
    bool Is(string type);
    string Type();

    void AddObjective(float x, float y);
    void AddObjective(Point pos);
    void Go(Point pos);
    void Move (float dt);
    

private:
    Sprite character;
	Point objective;
	int objectiveX, objectiveY;
    Timer temp;
    int crt;

};

#endif // PERMONKEY_H
