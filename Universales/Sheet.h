#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Text.h"

class Sheet{
public:
	Sheet();
	~Sheet();

	void SetObjectList(unordered_map<string, Attributes> objects);

	void RenderObjectSheet();
	void UpdateObjectSheet();

	bool IsInside(int px, int py);
	bool IsBuy(int mouseX, int mouseY);

	Attributes GetAttributes();

private:
	Sprite sheet, objectSprite, buy;
	Rect box, buyBox;
	unordered_map<string, Attributes> objects;
	vector<Text*> objNames;
	//vector<Text*> attributesInfo;
	Text attributesInfo[3];
	int itemSelected;
};

