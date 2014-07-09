#ifndef GUI_H
#define GUI_H

#include "Sprite.h"
#include "Rect.h"


enum GuiState{
	BASIC = 0,
	ROOMS,
	EDIT_WALL_GUI,
	EDIT,
};

class GUI{
public:
	GUI();
    GUI(string file1, string file2, string file3, string file4);
	GUI(string file1, string file2);
    ~GUI();
    void Render();
    void SetPosition(float x, float y);
    void SetPosition(Point p);
	void SetState(GuiState newState);
	bool DoorIconPressed();
	bool MoveWallPressed();
	bool ExpandwallPressed();
	bool WallIconPressed();
    bool BuildIconPressed();
    bool DestroyIconPressed();
	bool BuyIconPressed();
	bool EditIconPressed();
	bool PirateIconPressed();
	bool SamuraiIconPressed();
    bool IsInside();
	void SetFrameBuildIcon(int currentFrame);
	void SetFrameDestroyIcon(int currentFrame);

private:
    Rect box, buildBox, destroyBox, buyBox, editBox, roomBox, pirateBox, samuraiBox, doorBox, wallBox, movewallBox, expandwallBox;
    Sprite buildIcon, destroyIcon, buyIcon, editIcon, pirateIcon, samuraiIcon, doorIcon, wallIcon, movewallIcon, expandwallIcon;
	GuiState guiState;

};

#endif // GUI_H
