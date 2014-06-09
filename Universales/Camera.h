#ifndef CameraH
#define CameraH

#include "GameObject.h"
#include "InputManager.h"
#include <memory>

class Camera {
private:
	static GameObject* focus;
public:
	static Point pos;
	static float speed;
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
};

#endif