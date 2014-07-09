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
	void Update();
	void SetName(string id);
	void SetCost(string hunger);
	void SetDescription(string description);
	void SetRender(bool render);
	bool GetRender();
	bool GetSell();
	bool GetMove();
	int GetPrice();
	Rect GetBox();

private:
	CharType charType;
	Sprite picture, sheet, moveIcon, sellIcon;
	Rect sheetBox, sellBox, moveBox;
	Text name, description, cost;
	bool render, sell, move;
	int price;
};

