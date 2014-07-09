#include "ObjectSheet.h"
#include "InputManager.h"

ObjectSheet::ObjectSheet() : picture(""), sheet("img/characterSheet.png"), moveIcon("img/icons/icone_mover.png", 2, -1), sellIcon("img/icons/icone_venda.png", 2, -1), name("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "shajda", WHITE, 1400 - sheet.GetWidth() + 20, 20), description("font/SFPixelate.ttf", 15, Text::TEXT_WRAPPED, "Description:", WHITE, 1400 - sheet.GetWidth() + 15, 145, sheet.GetWidth() - 25), cost("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Sell Price:", WHITE, 1400 - sheet.GetWidth() + 15, 125){
	render = false;
	sell = false;
	move = false;

}
ObjectSheet::ObjectSheet(vector<string> info) : picture(info[2]), sheet("img/characterSheet.png"), moveIcon("img/icons/icone_mover.png", 2, -1), sellIcon("img/icons/icone_venda.png", 2, -1), name("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, info[0], WHITE, 1400 - sheet.GetWidth() + 20, 20), description("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Description:" + info[1], WHITE, 1400 - sheet.GetWidth() + 15, 145), cost("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "Sell Price:" + info[3], WHITE, 1400 - sheet.GetWidth() + 15, 125){
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
	price = stoi(info[3]) / 3;
	cost.SetText("Sell Price:" + to_string(price));
	sheetBox.x = 1400 - sheet.GetWidth();
	sheetBox.y = 5;
	sheetBox.h = sheet.GetHeight();
	sheetBox.w = sheet.GetWidth();
	sellBox = Rect(sheetBox.x + sheetBox.w - moveIcon.GetWidth() - 12 - sellIcon.GetWidth(), sheetBox.y + sheetBox.h - moveIcon.GetHeight() - 15, sellIcon.GetWidth(), sellIcon.GetHeight());
	moveBox = Rect(sheetBox.x + sheetBox.w - moveIcon.GetWidth() - 10, sheetBox.y + sheetBox.h - moveIcon.GetHeight() - 15, moveIcon.GetWidth(), moveIcon.GetHeight());
}

ObjectSheet::~ObjectSheet(){

}

void ObjectSheet::Update(){
	Point pos = Point(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
	if (sellBox.IsInside(pos.x, pos.y)){
		sellIcon.SetFrame(2);
	}
	else{
		sellIcon.SetFrame(1);
	}
	if (moveBox.IsInside(pos.x, pos.y)){
		moveIcon.SetFrame(2);
	}
	else{
		moveIcon.SetFrame(1);
	}

	if (InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){
		if (sellBox.IsInside(pos.x, pos.y)){
			sell = true;
			render = false;
		}
		if (moveBox.IsInside(pos.x, pos.y)){
			move = true;
			render = false;
		}
	}
}

void ObjectSheet::Render(){
	sheet.Render(sheetBox.x, sheetBox.y);
	picture.Render(sheetBox.x + 20, sheetBox.y + 40);
	moveIcon.Render(sheetBox.x + sheetBox.w - moveIcon.GetWidth() - 10, sheetBox.y + sheetBox.h - moveIcon.GetHeight() - 15);
	//sellIcon.Render(sheetBox.x + sheetBox.w - moveIcon.GetWidth() - 12 - sellIcon.GetWidth(), sheetBox.y + sheetBox.h - moveIcon.GetHeight() - 15);
	name.Render();
	cost.Render();
	//description.Render();
	
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
	sell = false;
	move = false;
}

int ObjectSheet::GetPrice(){
	return price;
}

bool ObjectSheet::GetMove(){
	return move;
}

bool ObjectSheet::GetSell(){
	return sell;
}
