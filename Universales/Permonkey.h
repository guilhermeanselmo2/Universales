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
	Permonkey(float x, float y, TileMap tileMap);
    ~Permonkey();
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision (GameObject& other);
    bool Is(string type);
    string Type();

	void AddObjective(float x, float y, Point tile);
    void AddObjective(Point pos);
    void Go(Point pos);
    void Move (float dt);
    

private:
	Character::ActionCharacter actionCharacter;
	Sprite character;
	Point permonkeyTile;
	Point objectiveTile;
	Point objective;
	Point objectiveMem;
	Timer temp;
	int crt;
	Point desvio;
	bool flagDesvio;
	TileMap tileMap;

};

#endif // PERMONKEY_H
