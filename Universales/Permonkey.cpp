#include "Permonkey.h"
#include "Camera.h"

Permonkey::Permonkey(float x, float y) : character("img/permacaco_anim_ss.png", 4, 0.5, 4) {
    box = Rect(x-character.GetWidth()/2,y-character.GetHeight()/2, character.GetWidth(), character.GetHeight());
    rotation = 0;
    roomID = 0;
    crt = 0;
    objective.x = 994;
    objective.y = 470;
}

Permonkey::~Permonkey(){


}

void Permonkey::Update(float dt){
    character.Update(dt);
    Move(dt);
}

void Permonkey::Render(int cameraX, int cameraY){
    character.Render(box.x+Camera::pos.x, box.y+Camera::pos.y-box.h/2, rotation);
}

bool Permonkey::IsDead(){
	return false;

}

void Permonkey::NotifyCollision(GameObject &other){

}

bool Permonkey::Is(string type){
    return type == "PerMonkey";
}

string Permonkey::Type(){
    return "PerMonkey";
}

void Permonkey::AddObjective(float x, float y){
    if (crt >= 0)
        crt++;
    objective.x = x;
    objective.y = y;
}

void Permonkey::AddObjective(Point pos){
    if (crt >= 0)
        crt++;
    objective = pos;
}

void Permonkey::Go(Point pos){
    objective = pos;
}

void Permonkey::Move(float dt){
    temp.Update(dt);
    Point center_pos;
    center_pos.x = box.x+character.GetWidth()/2;
    center_pos.y = box.y+character.GetHeight()/2;
    float distance = objective.GetDistance(box.x+character.GetWidth()/2, box.y+character.GetHeight()/2 );
        if (distance< 3) {
            box.x = objective.x;
            box.y = objective.y;
            box = Rect(box.x-character.GetWidth()/2,box.y-character.GetHeight()/2, character.GetWidth(), character.GetHeight());
        }

        if (distance > 3 && temp.Get() > 0.001) {
            if (((objective.x != center_pos.x) || (objective.y != center_pos.y)) && ((objective.y > 0) && (objective.x > 0))) {
                if ((objective.x != center_pos.x) && (objective.y != center_pos.y)) {

                    if ((center_pos.x < objective.x) && (center_pos.y < objective.y)){
                        box.x += 2;
                        box.y += 1;
                    }
                    if ((center_pos.x > objective.x) && (center_pos.y < objective.y)){
                        box.x -= 2;
                        box.y += 1;
                    }

                    if ((center_pos.x < objective.x) && (center_pos.y > objective.y)){
                        box.x += 2;
                        box.y -= 1;
                    }
                    if ((center_pos.x > objective.x) && (center_pos.y > objective.y)){
                        box.x -= 2;
                        box.y -= 1;
                    }
                }

                if ((objective.x == center_pos.x) && (objective.y != center_pos.y)) {
                    if ((center_pos.y < objective.y)){
                        box.x += 2;
                        box.y += 1;
                    }

                    if ((center_pos.y > objective.y)){
                        box.x -= 2;
                        box.y -= 1;
                    }
                }
                if ((objective.x != center_pos.x) && (objective.y == center_pos.y)) {
                    if ((center_pos.x < objective.x)){
                        box.x += 2;
                        box.y -= 1;
                    }

                    if ((center_pos.x > objective.x)){
                        box.x -= 2;
                        box.y += 1;
                    }
                }
            }

            else {
                //Stop;
            }
            //box = Rect(tile_pos.x-character.GetWidth()/2,tile_pos.y-character.GetHeight()/2, character.GetWidth(), character.GetHeight());
            temp.Restart();
        }
}
