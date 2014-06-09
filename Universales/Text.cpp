#include "Text.h"

std::unordered_map<std::string, TTF_Font*> Text::assetTable;

Text::Text() {}

Text::Text(string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, int x, int y) : fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color) {
	texture = NULL;
	font = NULL;
	box.SetRect(x, y, box.GetWrect(), box.GetHrect());

	string key = fontFile + std::to_string(fontSize);

	if (assetTable.find(key) != assetTable.end()){
		std::cout << "Arquivo carregado ..." << std::endl;
	}

	if (assetTable.find(key) == assetTable.end()){
		std::cout << "Arquivo nao encontrado... carregando arquivo... " << std::endl;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
		assetTable.emplace(key, font);
	}

	font = TTF_OpenFont(fontFile.c_str(), fontSize);

	if (font != NULL){
		RemakeTexture();
	}
}

Text::~Text() {
	if (texture != NULL)
		SDL_DestroyTexture(texture);
}

void Text::Render(int cameraX, int cameraY) {
	SDL_Rect dstrec, clipRect;
	dstrec.x = box.GetXrect() - cameraX;
	dstrec.y = box.GetYrect() - cameraY;
	dstrec.w = box.GetWrect();
	dstrec.h = box.GetHrect();
	clipRect.x = 0;
	clipRect.y = 0;
	clipRect.w = box.GetWrect();
	clipRect.h = box.GetHrect();
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrec);
}

void Text::SetPos(int x, int y, bool centerX, bool centerY){
	if (centerX)
		x = x - box.GetXrect() / 2;
	if (centerY)
		y = y - box.GetYrect() / 2;
	box.SetRect(x,y,box.GetWrect(),box.GetHrect());
}

void Text::SetText(string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	string key = fontFile + std::to_string(fontSize);

	if (assetTable.find(key) != assetTable.end()){
		std::cout << "Arquivo carregado ..." << std::endl;
	}

	if (assetTable.find(key) == assetTable.end()){
		std::cout << "Arquivo nao encontrado... carregando arquivo... " << std::endl;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
		assetTable.emplace(key, font);
	}

	font = assetTable.at(key);

	if (font != NULL)
		RemakeTexture();
}

void Text::Clear() {
	for (auto element = assetTable.begin(); element != assetTable.end(); element++) {
		TTF_CloseFont(element->second);
	}
}

void Text::RemakeTexture() {

	SDL_Surface *surface = NULL;
	int w, h;
	if (texture != NULL)
		texture = NULL;

	switch (style)
	{
	case TEXT_SOLID:
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
		break;
	case TEXT_SHADED:
		surface = TTF_RenderText_Shaded(font, text.c_str(), color, SDL_Color());
		break;
	case TEXT_BLENDED:
		surface = TTF_RenderText_Blended(font, text.c_str(), color);
		break;
	default:
		cout << "Estilo desconhecido!" << endl;
	}
	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, 0, 0, &w, &h);
	box.SetRect(box.GetXrect(),box.GetYrect(), w, h);
}