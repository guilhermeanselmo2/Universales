#include "CharacterSheet.h"


CharacterSheet::CharacterSheet(CharType type) : picture("img/permacaco.png"), sheet("img/characterSheet.png"), race("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Permonkey", WHITE, 1024 - sheet.GetWidth() + 20, 20), hunger("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Hunger:", WHITE, 1024 - sheet.GetWidth() + 110, 45), satisfaction("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Satisfaction:", WHITE, 1024 - sheet.GetWidth() + 110, 105), money("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Money:", WHITE, 1024 - sheet.GetWidth() + 110, 165){
	hungerVal = hunger;
	hungerVal.SetPos(1024 - sheet.GetWidth() + 110, 60);
	moneyVal = money;
	moneyVal.SetPos(1024 - sheet.GetWidth() + 110, 180);
	satisfactionVal = satisfaction;
	satisfactionVal.SetPos(1024 - sheet.GetWidth() + 110, 120);
	sheetBox.x = 1024 - sheet.GetWidth();
	sheetBox.y = 5;
	sheetBox.h = sheet.GetHeight();
	sheetBox.w = sheet.GetWidth();
	charType = type;
	render = false;
}

CharacterSheet::~CharacterSheet(){

}

void CharacterSheet::Render(){
	sheet.Render(sheetBox.x, sheetBox.y);
	picture.Render(sheetBox.x+20, sheetBox.y+40);
	race.Render();
	satisfaction.Render();
	satisfactionVal.Render();
	money.Render();
	moneyVal.Render();
	hunger.Render();
	hungerVal.Render();
}

void CharacterSheet::SetRace(string id){
	switch (charType)
	{
	case PERMONKEY:
		race.SetText("Permonkey : " + id);
		break;
	default:
		break;
	}
}

void CharacterSheet::SetHunger(string hunger){
	this->hungerVal.SetText(hunger);
}

void CharacterSheet::SetSatisfaction(string satisfaction){
	this->satisfactionVal.SetText(satisfaction);
}

void CharacterSheet::SetMoney(string money){
	this->moneyVal.SetText(money);
}

bool CharacterSheet::GetRender(){
	return render;
}

Rect CharacterSheet::GetBox(){
	return sheetBox;
}

void CharacterSheet::SetRender(bool render){
	this->render = render;
}
