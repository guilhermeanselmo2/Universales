#include "State.h"
#include "Collision.h"
#include "Camera.h"
#include "TileMap.h"


State::State() {
	requestDelete = false;
	requestQuit = false;
}

State::~State() {}

void State::AddObject(GameObject* object) {
	objectArray.emplace_back(object);
}

bool State::RequestedDelete() {
	return requestDelete;
}

bool State::RequestedQuit() {
	return requestQuit;
}

void State::UpdateArray(float dt, TileMap *tileMap) {
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i]->Update(dt);
	}
	for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
        Point p(objectArray[i]->box.x,objectArray[i]->box.y+objectArray[i]->box.h);
        if(objectArray[i]->Is("Wall")){
            p.SetPoint(p.x + tileMap->GetTileWidth()/2,p.y-tileMap->GetTileHeight()/4);
        }
        p = tileMap->GetTile(p.x, p.y);
        if(objectArray[i]->Is("Wall")){
        }
		p.SetPoint(i,p.x,p.y);
        renderQueue.emplace(p);
    }
	/*for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;
		}
	}
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		for (int k = 0; k < objectArray.size(); k++) {
			if (Collision::IsColliding(objectArray[i]->box, objectArray[k]->box, objectArray[i]->rotation, objectArray[k]->rotation)) {
				objectArray[i]->NotifyCollision(*objectArray[k]);
				objectArray[k]->NotifyCollision(*objectArray[i]);
				break;
			}
		}
	}*/
}

void State::RenderArray() {
	/*for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render((int)Camera::pos.GetXpoint(), (int)Camera::pos.GetYpoint());
	}*/
	while (!renderQueue.empty()) {
        //cout  << renderQueue.top().x << "," << renderQueue.top().y << "," << renderQueue.top().z << endl;
        //cout << "Rendering "<< objectArray[renderQueue.top().x]->Type() << " at : " << renderQueue.top().y << "," << renderQueue.top().z << endl;
        objectArray[renderQueue.top().x]->Render(0,0);

        renderQueue.pop();
    }
}