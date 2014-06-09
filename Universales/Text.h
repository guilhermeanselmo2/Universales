#ifndef TextH
#define TextH

#include "Game.h"

class Text {

public:
	enum TextStyle{
		TEXT_SOLID = 0,
		TEXT_SHADED,
		TEXT_BLENDED,
	};
	Text();
	Text (string fontFile, int fontSize,TextStyle style, string text, SDL_Color color, int x = 0, int y = 0);
	~Text ();
	void Render (int cameraX = 0, int cameraY = 0);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);
	void SetText(string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
	static void Clear();

private:
	void RemakeTexture();
	TTF_Font* font;
	SDL_Texture* texture;
	string fontFile;
	string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	Rect box;
	static std::unordered_map<std::string, TTF_Font*> assetTable;

};

#endif