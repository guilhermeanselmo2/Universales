#include "Sprite.h"

unordered_map<string, SDL_Texture*> Sprite::assetTable;

Sprite::Sprite() {
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	frameCount = 1;
	frameHeight = 1;
	frameTime = 1;
	currentFrame = 0;
	currentHeight = 0;	
}

Sprite::Sprite(string file, int frameCount, float frameTime, float frameHeight) : frameCount(frameCount), frameTime(frameTime), frameHeight(frameHeight) {
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	currentFrame = 0;
	currentHeight = 0;
	Open(file);
}

void Sprite::Update(float dt) {
	timeElapsed += dt;
	if (frameCount > 1){
		if (timeElapsed >= frameTime){
			if (currentFrame >= frameCount)
				currentFrame = 0;
			SetClip(GetWidth()*currentFrame, clipRect.h*currentHeight, clipRect.w, clipRect.h);
			currentFrame++;
			timeElapsed = 0;
		}
	}
	if (frameCount == 1)
		SetClip(0, 0, clipRect.w, clipRect.h);
}

void Sprite::SetFrame(int frame) {
	float  clipSet = 0;
	clipSet = (frame-1)*GetWidth();
	SetClip(clipSet, 0, dimensions.w / frameCount, dimensions.h);
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;
}

int Sprite::GetTotalWidth() const {
	return dimensions.w*scaleX;
}

Sprite :: ~Sprite() {}

void Sprite::Open(string file) {

	if (assetTable.find(file) != assetTable.end()){
		cout << "Arquivo carregado ..." << endl;
	}

	if (assetTable.find(file) == assetTable.end()){
		cout << "Arquivo "<< file << " nao encontrado... carregando arquivo... " << endl;
		texture = (SDL_Texture*)IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		assetTable.emplace(file, texture);
	}

	texture = assetTable.at(file);
	SDL_QueryTexture(texture, NULL, NULL, &dimensions.w, &dimensions.h);
	SetClip(0, 0, dimensions.w/frameCount, dimensions.h/frameHeight);
}

void Sprite::Clear() {
	for (auto element = assetTable.begin(); element != assetTable.end(); element++) {
		SDL_DestroyTexture(element->second);
	}
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle){
	SDL_Rect dstrec;
	dstrec = dimensions;
	dstrec.x = x;
	dstrec.y = y;
	dstrec.w = clipRect.w*scaleX;
	dstrec.h = clipRect.h*scaleY;

	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrec,angle,NULL,SDL_FLIP_NONE);
	Update(Game::GetInstance().GetDeltaTime());
}

int Sprite::GetHeight() const {
	return dimensions.h*scaleY/frameHeight;
}

int Sprite::GetWidth() const {
	return dimensions.w*scaleX/frameCount;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}
void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}

bool Sprite::IsOpen() {
	if (texture)
		return true;
	else
		return false;
}