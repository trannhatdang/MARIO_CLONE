#ifndef CAMERA_H_
#define CAMERA_H_

#include "engine/Components/Component.h"
#include "engine/main.h"
#include "Config.h"

class Camera : public Component
{
	private:
		GameObject* m_player;
		void (*m_setCameraPosFunc)(Vector3);
	public:
		Camera(GameObject* obj, GameObject* player, void (*setCameraPosFunc)(Vector3));
		~Camera();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
