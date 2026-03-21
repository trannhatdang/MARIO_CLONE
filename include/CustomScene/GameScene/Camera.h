#ifndef CAMERA_H_
#define CAMERA_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/main.h"
#include "Config.h"

class Camera : public Component
{
	private:
		Transform* m_tfs;
		Transform* m_player_tfs;
		GameObject* m_player;
		void (*m_setCameraPosFunc)(Vector3);

		void moveLeft();
		void moveRight();
	public:
		Camera(GameObject* obj, GameObject* player, void (*setCameraPosFunc)(Vector3));
		~Camera();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
