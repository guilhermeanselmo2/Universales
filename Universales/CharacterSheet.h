#pragma once
#include "Sprite.h"
#include "Character.h"
#include "Rect.h"
#include "Text.h"

class CharacterSheet
{
public:
	CharacterSheet(CharType type);
	~CharacterSheet();
	void Render();
	void SetRace(string id);
	void SetHunger(string hunger);
	void SetSatisfaction(string satisfaction);
	void SetMoney(string money);
	void SetRender(bool render);
	bool GetRender();
	Rect GetBox();

private:
	CharType charType;
	Sprite picture, sheet;
	Rect sheetBox;
	Text race, hunger, satisfaction, money;
	Text hungerVal, satisfactionVal, moneyVal;
	bool render;
};

