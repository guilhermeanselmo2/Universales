#include "ObjectSheet.h"
ObjectSheet::ObjectSheet() : picture(""), sheet("img/characterSheet.png"), name("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "shajda", WHITE, 1400 - sheet.GetWidth() + 20, 20), description("font/SFPixelate.ttf", 15, Text::TEXT_WRAPPED, "Description:", WHITE, 1400 - sheet.GetWidth() + 15, 145, sheet.GetWidth()-25), cost("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Sell Price:", WHITE, 1400 - sheet.GetWidth() + 15, 125){
	render = false;

}
ObjectSheet::ObjectSheet(vector<string> info) : picture(info[2]), sheet("img/characterSheet.png"), name("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, info[0], WHITE, 1400 - sheet.GetWidth() + 20, 20), description("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Description:"+info[1], WHITE, 1400 - sheet.GetWidth() + 15, 145), cost("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Sell Price:" + info[3], WHITE, 1400 - sheet.GetWidth() + 15, 125){
	sheetBox.x = 1400 - sheet.GetWidth();
	sheetBox.y = 5;
	sheetBox.h = sheet.GetHeight();
	sheetBox.w = sheet.GetWidth();
	render = false;
}

void ObjectSheet::Open(vector<string> info){
	picture.Open(info[2]);
	name.SetText(info[0]); 
	description.SetText(info[1]);
	cost.SetText("Sell Price:" + info[3]);
	sheetBox.x = 1400 - sheet.GetWidth();
	sheetBox.y = 5;
	sheetBox.h = sheet.GetHeight();
	sheetBox.w = sheet.GetWidth();
}

ObjectSheet::~ObjectSheet(){

}

void ObjectSheet::Render(){
	sheet.Render(sheetBox.x, sheetBox.y);
	picture.Render(sheetBox.x + 20, sheetBox.y + 40);
	name.Render();
	cost.Render();
	description.Render();
}

void ObjectSheet::SetName(string id){
	name.SetText(id);

}

void ObjectSheet::SetCost(string cost){
	this->cost.SetText("Sell Price:" + cost);
}

void ObjectSheet::SetDescription(string description){
	this->description.SetText(description);
}


bool ObjectSheet::GetRender(){
	return render;
}

Rect ObjectSheet::GetBox(){
	return sheetBox;
}

void ObjectSheet::SetRender(bool render){
	this->render = render;
}
