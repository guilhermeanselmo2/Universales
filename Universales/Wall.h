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
    INF_CORNER,
};


class Wall : public GameObject{
public:
    Wall(float centerX, float centerY, string file, WallStyle lStyle, Point lTile, int lRoom = 0);
    ~Wall();

	void Update(float dt, vector<unique_ptr<GameObject>> *objectArray);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(string type);
	bool IsCharacter();
	void Editing(bool editing);
    string Type();
	void AddObjective(float x, float y, Point tile);
	void AddObjective(vector<int> path);
	string GetChoice();
	Point GetTile();

	//Non Wall functions
	void SetHunger(int hunger);
	int GetHunger();
	void MoveTo(int x, int y);
	bool SettlePos(vector<int> obstacleMap);
	ActionCharacter GetAction();
	int GetObjectIndex();
	vector<int> GetHeuristic(int i);
	void UseObject(vector<unique_ptr<GameObject>> *objectArray, int index);
	vector<int> GetAttributes();
	vector<Point> GetAccessPoints();
	vector<string>GetTextAttributes();
	Rect GetBox();
	void Save(ofstream &file);

private:
	Timer editTimer;
	bool editing;
    Sprite wall;
    WallStyle style;

};

#endif //WALL_H
