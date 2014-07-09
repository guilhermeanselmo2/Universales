#pragma once
#include "Sprite.h"
#include "Object.h"
#include "Rect.h"
#include "Text.h"

class ObjectSheet
{
public:
	ObjectSheet();
	ObjectSheet(vector<string> info);
	void Open(vector<string> info);
	~ObjectSheet();
	void Render();
	void SetName(string id);
	void SetCost(string hunger);
	void SetDescription(string description);
	void SetRender(bool render);
	bool GetRender();
	Rect GetBox();

private:
	CharType charType;
	Sprite picture, sheet;
	Rect sheetBox;
	Text name, description, cost;
	bool render;
};

