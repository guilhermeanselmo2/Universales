#pragma once
#include <unordered_map>
#include <string.h>
#include "Room.h"
#include "Text.h"

class RoomSheet
{
public:
	RoomSheet();
	~RoomSheet();

	void SetRoomList(unordered_map<string, RoomAttributes> rooms);

	void RenderRoomSheet();
	void UpdateObjectSheet();

	bool IsInside(int px, int py);
	bool IsBuy(int mouseX, int mouseY);

	RoomAttributes GetAttributes();

private:
	Sprite sheet, roomSprite, buy;
	Rect box, buyBox;
	unordered_map<string, RoomAttributes> roomAttributes;
	vector<Text*> roomTypes;
	//vector<Text*> attributesInfo;
	Text attributesInfo[3];
	int typeSelected;

};

