#ifndef SpriteH
#define SpriteH

#include <unordered_map>
#include "Game.h"

using namespace std;

class Sprite {
private:
	SDL_Texture* texture;
	SDL_Rect dimensions;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;
	int frameCount, frameHeight;
	int currentFrame, currentHeight;
	float timeElapsed;
	float frameTime;

public:
	static unordered_map<string, SDL_Texture*> assetTable;
	Sprite();
	Sprite(string file, int frameCount = 1, float frameTime = 1, float frameHeight = 1);
	~Sprite();
	static void Clear();
	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, float angle = 0);
	int GetWidth() const;
	int GetTotalWidth() const;
	int GetHeight() const;
	bool IsOpen();
	void SetScaleX(float scale);
	void SetScaleY(float scale);
};

#endif