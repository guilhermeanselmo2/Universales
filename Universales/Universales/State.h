#ifndef StateH
#define StateH

#include "GameObject.h"
#include "Comparator.h"
#include "TileMap.h"
#include "StateData.h"
#include "Character.h"

#include <vector>
#include <memory>
#include <queue>

using namespace std;

class State {
public:
	State();
	virtual ~State();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void AddObject(GameObject* object);
	bool RequestedDelete();
	bool RequestedQuit();
	StateData *data;
protected:
	bool requestDelete;
	bool requestQuit;
	virtual void UpdateArray(float dt, TileMap *tileMap);
	virtual void RenderArray();
	vector<unique_ptr<GameObject>> objectArray;
	vector<unique_ptr<Character>> characterArray;
	priority_queue<Point, vector<Point>,Comparator> renderQueue;

};

#endif