#include "RoomSheet.h"
#include "InputManager.h"


RoomSheet::RoomSheet() : sheet("img/objectPrev.png"), roomSprite(""), buy("img/icons/buy2.png"){
	box = Rect(700 - sheet.GetWidth() / 2, 20, sheet.GetWidth(), sheet.GetHeight());
	buyBox = Rect(box.x + box.w - 100, box.y + box.h - 100, buy.GetWidth(), buy.GetHeight());
	typeSelected = -1;
	attributesInfo[0] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "", WHITE, box.x + 450, 55);
	attributesInfo[1] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "", WHITE, box.x + 450, 225);
	attributesInfo[2] = Text("font/SFPixelate.ttf", 15, Text::TEXT_WRAPPED, "", WHITE, box.x + 410, 240, 370);
}


RoomSheet::~RoomSheet(){
}

void RoomSheet::UpdateObjectSheet(){
	if (InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){
		typeSelected = -1;
		for (int i = 0; i < roomTypes.size(); i++){
			if (roomTypes[i]->box.IsInside(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
				roomTypes[i]->SetStyle(Text::TEXT_SHADED);
				typeSelected = i;
				string name = roomTypes[i]->GetText();
				attributesInfo[0].SetText(name);
				attributesInfo[1].SetText(to_string(roomAttributes[name].cost));
				attributesInfo[2].SetText(roomAttributes[name].description);
				if (roomAttributes[name].description.size() < 37){
					cout << roomAttributes[name].type << " : " << roomAttributes[name].description.size() << endl;
					attributesInfo[2].SetStyle(Text::TEXT_SOLID);
				}
				else{
					cout << roomAttributes[name].type << " : " << roomAttributes[name].description.size() << endl;
					attributesInfo[2].SetStyle(Text::TEXT_WRAPPED);
				}
				roomSprite.Open(roomAttributes[name].tileSprite);
				/*attributesInfo[3] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].activeHunger), WHITE, box.x + 35, 40);
				attributesInfo[4] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].cost), WHITE, box.x + 35, 40);
				attributesInfo[5] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].cost), WHITE, box.x + 35, 40);
				attributesInfo[6] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].cost), WHITE, box.x + 35, 40);*/
			}
		}
	}

	for (int i = 0; i < roomTypes.size(); i++){
		if (roomTypes[i]->box.IsInside(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
			roomTypes[i]->SetStyle(Text::TEXT_SHADED);
		}
		else{
			if (i != typeSelected)
				roomTypes[i]->SetStyle(Text::TEXT_SOLID);
		}
	}
	
}

void RoomSheet::RenderRoomSheet(){
	sheet.Render(box.x, box.y);
	for (int i = 0; i < roomTypes.size(); i++){
		roomTypes[i]->Render();
	}
	if (typeSelected != -1){
		for (int i = 0; i < 3; i++){
			attributesInfo[i].Render();
		}
		roomSprite.Render(box.x + 450, 80);
		buy.Render(buyBox.x, buyBox.y);
	}
}

bool RoomSheet::IsInside(int px, int py){
	return box.IsInside(px, py);
}

bool RoomSheet::IsBuy(int mouseX, int mouseY){
	return buyBox.IsInside(mouseX, mouseY);
}

void RoomSheet::SetRoomList(unordered_map<string, RoomAttributes> rooms){
	cout << "Entrou setRoom" << endl;
	roomAttributes = rooms;
	vector <Text*> names;
	int counter = 1;
	for (auto it = roomAttributes.begin(); it != roomAttributes.end(); ++it){
		Text *name = new Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, it->second.type, WHITE, box.x + 35, 40 + 15 * counter);
		counter++;
		names.emplace_back(name);
	}
	roomTypes = names;
}

RoomAttributes RoomSheet::GetAttributes(){
	string name = roomTypes[typeSelected]->GetText();
	return roomAttributes[name];
}
