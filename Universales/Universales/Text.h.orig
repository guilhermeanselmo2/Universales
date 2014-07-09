#ifndef TextH
#define TextH

#include "Game.h"

static const SDL_Color WHITE = { 255, 255, 255 };
static const SDL_Color BLUE = { 0, 0, 255 };
static const SDL_Color LIGHT_BLUE = { 33, 211, 203 };
static const SDL_Color BLACK = { 0, 0, 0 };

class Text {

public:
	enum TextStyle{
		TEXT_SOLID = 0,
		TEXT_SHADED,
		TEXT_BLENDED,
		TEXT_WRAPPED,
	};
	Text();
	Text (string fontFile, int fontSize,TextStyle style, string text, SDL_Color color, int x = 0, int y = 0, int width=0);
	~Text ();
	void Render (int cameraX = 0, int cameraY = 0);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);
	void SetText(string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
	static void Clear();

	string GetText();
	Rect box;
private:
	void RemakeTexture();
	int width, heigh, widthLimit;
	TTF_Font* font;
	SDL_Texture* texture;
	string fontFile;
	string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	static std::unordered_map<std::string, TTF_Font*> assetTable;

};

#endif