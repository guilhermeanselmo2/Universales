#ifndef GUI_H
#define GUI_H

#include "Sprite.h"
#include "Rect.h"


enum GuiState{
	BASIC = 0,
	ROOMS,
};

class GUI{
public:
    GUI();
    ~GUI();
    void Render();
    void SetPosition(float x, float y);
    void SetPosition(Point p);
	void SetState(GuiState newState);
    bool BuildIconPressed();
    bool DestroyIconPressed();
	bool BuyIconPressed();
	bool EditIconPressed();
	bool PirateIconPressed();
	bool SamuraiIconPressed();
    bool IsInside();

private:
    Rect box, buildBox, destroyBox, buyBox, editBox, roomBox, pirateBox, samuraiBox;
    Sprite buildIcon, destroyIcon, buyIcon, editIcon, pirateIcon, samuraiIcon;
	GuiState guiState;

};

#endif // GUI_H
