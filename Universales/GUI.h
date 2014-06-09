#ifndef GUI_H
#define GUI_H

#include "Sprite.h"
#include "Rect.h"


class GUI{
public:
    GUI();
    ~GUI();
    void Render();
    void SetPosition(float x, float y);
    void SetPosition(Point p);
    bool BuildIconPressed();
    bool DestroyIconPressed();
    bool IsInside();

private:
    Rect box, buildBox, destroyBox;
    Sprite buildIcon, destroyIcon;

};

#endif // GUI_H
