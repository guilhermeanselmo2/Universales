#ifndef SelectionBoxH
#define SelectionBoxH
#include "TileMap.h"
#include "Sprite.h"

class SelectionBox
{
public:
	SelectionBox(void);
	~SelectionBox(void);
	void Update(TileMap *TileMap);
    void Render(TileMap *tileMap);
    void SetBegin(float x, float y);
    void SetBegin(Point pos);
    Point begin;
    Point end;

private:

    Sprite sp;
};

#endif

