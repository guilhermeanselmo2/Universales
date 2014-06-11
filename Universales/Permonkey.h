#ifndef PERMONKEY_H
#define PERMONKEY_H

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <queue>

class Permonkey : public GameObject{
public:
    Permonkey(float x, float y, Point lTile);
    ~Permonkey();
	void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision (GameObject& other);
    bool Is(string type);
	bool IsCharacter();
    string Type();

    void AddObjective(float x, float y);
    void AddObjective(Point pos);
    void Go(Point pos);
	void PathAStar(Point pos, vector<int> heuristic, vector<int> occupancyGrid);
	void PathAStar(int posX, int posY, vector<int> heuristic, vector<int> occupancyGrid);
    void Move (float dt);
    

private:
    Sprite character;
	Point objective;
	int objectiveX, objectiveY;
    Timer temp;
    int crt;

};

#endif // PERMONKEY_H
