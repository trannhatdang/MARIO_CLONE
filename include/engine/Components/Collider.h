#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "engine/Components/Component.h"
#include "engine/main.h"
#include <algorithm>
#include <unordered_set>

class Rigidbody;

//Only 2D and only box, normally this should inherit another collider component but this should do

class Collider : public Component
{
	private:
		bool m_trigger = false;
		bool m_debug = false;
		bool m_custom_center = false;
		SDL_Rect m_rect;
		Vector3 m_center;
		std::unordered_set<GameObject*> m_objectsCollided;

		Vector3 findDisplacementVec(const Vector3& pos, const Vector3& dir) const;
		Vector3 findDirectionToPushAway(const Vector3& pos) const;
		void checkCollisionOfCurr();
	public:
		Collider(GameObject* gameObject, SDL_Rect rect, bool isTrigger = false);
		void CheckCollision();
		void OnStart();
		void OnIterate();
		void OnFixedIterate();
		void OnDraw(SDL_Renderer* renderer);
		void OnEvent(SDL_Event* event);
		void DoCollision(GameObject* other_obj);
		void Collide(GameObject* other_obj);
		SDL_Rect GetRect() const;
		Vector3 GetCenter() const;
		void SetCenter(const Vector3& center);
		Vector3 CheckPath(const Vector3& pos, const Vector3f& dir);
		GameObject* CheckCollision(const Vector3& pos) const;

		std::unique_ptr<Component> copy();
};

#endif
