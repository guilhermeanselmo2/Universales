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
    Permonkey(float x, float y, Point lTile, TileMap tileMap);
    ~Permonkey();
	void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision (GameObject& other);
    bool Is(string type);
	bool IsCharacter();
    string Type();
	void Editing(bool editing);
	void AddObjective(float x, float y, Point tile);
    void AddObjective(Point pos);
	void AddObjective(vector<int> path);
    void Go(Point pos);
	void PathAStar(Point pos, vector<int> heuristic, vector<int> occupancyGrid);
	void PathAStar(int posX, int posY, vector<int> heuristic, vector<int> occupancyGrid);
    void Move (float dt);
	void MakeChoice();
	int GetHunger();
	Choice GetChoice();
	
	void MoveTo(int x, int y);

    

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
	vector<int> path;
	int hunger;
	Choice choice;

};

#endif // PERMONKEY_H
