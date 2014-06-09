#include "SelectionBox.h"
#include "InputManager.h"
#include "Camera.h"


SelectionBox::SelectionBox(): sp("img/tileset/tile_tatami.png"){
    begin.SetPoint(0,0);
    end.SetPoint(0,0);
}

SelectionBox::~SelectionBox(){

}

void SelectionBox::Update(TileMap *tileMap){
    Point mousePosition(InputManager::GetInstance().GetMouseX(),InputManager::GetInstance().GetMouseY());
    end = tileMap->GetTile(mousePosition.x-Camera::pos.x, mousePosition.y-Camera::pos.y);
}

void SelectionBox::Render(TileMap *tileMap){
    Point renderPos;
    if(end.x < begin.x){
        if(end.y<begin.y){
            for(int i = end.x; i <= begin.x; i++){
                for(int j = end.y; j <= begin.y; j++){
                    if(i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
                        Point tile(i,j);
                        renderPos = tileMap->GetTileCenter(tile);
                        sp.Render(renderPos.x - sp.GetWidth()/2 + Camera::pos.x, renderPos.y - sp.GetHeight()/2+ Camera::pos.y);
                    }
                }
            }
        }else{
            for(int i = end.x; i <= begin.x; i++){
                for(int j = begin.y; j <= end.y; j++){
                    if(i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
                        Point tile(i,j);
                        renderPos = tileMap->GetTileCenter(tile);
                        sp.Render(renderPos.x - sp.GetWidth()/2 + Camera::pos.x, renderPos.y - sp.GetHeight()/2+ Camera::pos.y);
                    }
                }
            }
        }
    }
    else{
        if(end.y<begin.y){
            for(int i = begin.x; i <= end.x; i++){
                for(int j = end.y; j <= begin.y; j++){
                    if(i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
                        Point tile(i,j);
                        renderPos = tileMap->GetTileCenter(tile);
                        sp.Render(renderPos.x - sp.GetWidth()/2 + Camera::pos.x, renderPos.y - sp.GetHeight()/2+ Camera::pos.y);
                    }
                }
            }
        }else{
            for(int i = begin.x; i <= end.x; i++){
                for(int j = begin.y; j <= end.y; j++){
                    if(i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
                        Point tile(i,j);
                        renderPos = tileMap->GetTileCenter(tile);
                        sp.Render(renderPos.x - sp.GetWidth()/2 + Camera::pos.x, renderPos.y - sp.GetHeight()/2+ Camera::pos.y);
                    }
                }
            }
        }
    }

}

void SelectionBox::SetBegin(float x, float y){
    begin.x = x;
    begin.y = y;
}

void SelectionBox::SetBegin(Point pos){
    begin.x = pos.x;
    begin.y = pos.y;
}
