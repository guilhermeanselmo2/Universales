#ifndef GUI_H
#define GUI_H

#include "Sprite.h"
#include "Rect.h"


class GUI{
public:
	GUI();
    GUI(string file1, string file2, string file3, string file4);
	GUI(string file1, string file2);
    ~GUI();
    void Render();
    void SetPosition(float x, float y);
    void SetPosition(Point p);
	void SetPositionSubGUI(float x, float y);
	void SetPositionSubGUI(Point p);
	bool DoorIconPressed();
	bool WallIconPressed();
    bool BuildIconPressed();
    bool DestroyIconPressed();
	bool BuyIconPressed();
	bool EditIconPressed();
    bool IsInside();

private:
    Rect box, buildBox, destroyBox, buyBox, editBox, doorBox, wallBox;
    Sprite buildIcon, destroyIcon, buyIcon, editIcon, doorIcon, wallIcon;

};

#endif // GUI_H
