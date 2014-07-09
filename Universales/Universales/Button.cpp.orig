#include "Button.h"


Button::Button(string text, int size, int x, int y)
{
	content = text;
	texto = new Text("font/TRIBAL__.ttf", 20, Text::TEXT_BLENDED, text.c_str(), WHITE, 100);
	texto->SetPos(x, y, true, true);
	area = texto->box;
	pressed = false;
}


Button::~Button()
{
	delete texto;
}

void Button::Update(float dt){
	Point p(0, 0);
	p.x = InputManager::GetInstance().GetMouseX();
	p.y = InputManager::GetInstance().GetMouseY();
	
	bool click = InputManager::GetInstance().MouseRelease(1);

	if (area.IsInside(p.x,p.y)){
		texto->SetColor(BLUE);
		if (click){
			pressed = true;
		}
		else{
			pressed = false;
		}
	}
	else{
		texto->SetColor(WHITE);
	}
}

void Button::Render(){
	texto->Render();
}