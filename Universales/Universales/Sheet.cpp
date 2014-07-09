#include "Sheet.h"
#include "InputManager.h"


Sheet::Sheet() : sheet("img/objectPrev.png"), objectSprite(""), buy("img/icons/buy2.png"){
	box = Rect(700 - sheet.GetWidth() / 2, 20, sheet.GetWidth(), sheet.GetHeight());
	buyBox = Rect(box.x + box.w - 100, box.y + box.h - 100, buy.GetWidth(), buy.GetHeight());
	itemSelected = -1;
	typeSelected = -1;
	attributesInfo[0] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "", WHITE, box.x + 450, 55);
	attributesInfo[1] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, "", WHITE, box.x + 450, 225);
	attributesInfo[2] = Text("font/SFPixelate.ttf", 15, Text::TEXT_WRAPPED, "", WHITE, box.x + 410, 240, 370);
}


Sheet::~Sheet(){
}

void Sheet::UpdateObjectSheet(){
	if (InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){
		itemSelected = -1;
		if (typeSelected == -1){
			for (int i = 0; i < objTypes.size(); i++){
				if (objTypes[i]->box.IsInside(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
					typeSelected = i;
					string type = objTypes[i]->GetText();
					objTypes[i]->SetStyle(Text::TEXT_SHADED);
					SetObjectList(objectsTypes[type]);
				}
			}


		}
		else{
			for (int i = 0; i < objNames.size(); i++){
				if (objNames[i]->box.IsInside(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
					objNames[i]->SetStyle(Text::TEXT_SHADED);
					itemSelected = i;
					string name = objNames[i]->GetText();
					attributesInfo[0].SetText(name);
					attributesInfo[1].SetText(to_string(objects[name].cost));
					attributesInfo[2].SetText(objects[name].description);
					if (objects[name].description.size() < 37){
						cout << objects[name].name << " : " << objects[name].description.size() << endl;
						attributesInfo[2].SetStyle(Text::TEXT_SOLID);
					}
					else{
						cout << objects[name].name << " : " << objects[name].description.size() << endl;
						attributesInfo[2].SetStyle(Text::TEXT_WRAPPED);
					}
					objectSprite.Open(objects[name].sprite);
					/*attributesInfo[3] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].activeHunger), WHITE, box.x + 35, 40);
					attributesInfo[4] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].cost), WHITE, box.x + 35, 40);
					attributesInfo[5] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].cost), WHITE, box.x + 35, 40);
					attributesInfo[6] = Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, to_string(objects[name].cost), WHITE, box.x + 35, 40);*/
				}
			}
		}
	}

	if (InputManager::GetInstance().MouseRelease(SDL_BUTTON_RIGHT)){
		if (typeSelected != -1){
			typeSelected = -1;
			itemSelected = -1;
		}
	}

	if (typeSelected != -1){
		for (int i = 0; i < objNames.size(); i++){
			if (objNames[i]->box.IsInside(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
				objNames[i]->SetStyle(Text::TEXT_SHADED);
			}

			else{
				if (i != itemSelected)
					objNames[i]->SetStyle(Text::TEXT_SOLID);
			}
		}
	}
	else{
		for (int i = 0; i < objTypes.size(); i++){
			if (objTypes[i]->box.IsInside(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
				objTypes[i]->SetStyle(Text::TEXT_SHADED);
			}

			else{
				objTypes[i]->SetStyle(Text::TEXT_SOLID);
			}
		}
	}


}

void Sheet::RenderObjectSheet(){
	sheet.Render(box.x, box.y);
	if (typeSelected != -1){
		for (int i = 0; i < objNames.size(); i++){
			objNames[i]->Render();
		}
	}
	else{
		for (int i = 0; i < objTypes.size(); i++){
			objTypes[i]->Render();
		}
	}
	
	if (itemSelected != -1){
		for (int i = 0; i < 3; i++){
			attributesInfo[i].Render();
		}
		objectSprite.Render(box.x + 450, 80);
		buy.Render(buyBox.x, buyBox.y);
	}
}

bool Sheet::IsInside(int px, int py){
	return box.IsInside(px, py);
}

bool Sheet::IsBuy(int mouseX, int mouseY){
	return buyBox.IsInside(mouseX, mouseY);
}

void Sheet::SetTypeList(unordered_map<string, unordered_map<string, Attributes>> objects){
	cout << "Entrou" << endl;
	this->objectsTypes = objects;
	int counter = 1;
	for (auto it = objects.begin(); it != objects.end(); ++it){
		Text *type = new Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, it->first, WHITE, box.x + 35, 40+15*counter);
		counter++;
		cout << "Setting types : " << it->first << endl;
		objTypes.emplace_back(type);
	}
}

void Sheet::SetObjectList(unordered_map<string, Attributes> objects){
	cout << "Entrou" << endl;
	this->objects = objects;
	vector <Text*> names;
	int counter = 1;
	for (auto it = objects.begin(); it != objects.end(); ++it){
		Text *name = new Text("font/SFPixelate.ttf", 15, Text::TEXT_SOLID, it->second.name, WHITE, box.x + 35, 40 + 15 * counter);
		counter++;
		names.emplace_back(name);
	}
	objNames = names;
}

Attributes Sheet::GetAttributes(){
	string name = objNames[itemSelected]->GetText();
	return objects[name];
}