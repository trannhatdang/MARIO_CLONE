#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.h"
#include "engine/dg_time.h"
#include "../Animation.h"
#include "../AnimationNode.h"

class Animator : public Component
{
	private:
		SDL_Renderer* m_renderer;
		Vector3f m_anchor;
		AnimationNode* m_currNode = nullptr;
		AnimationNode* m_startNode;
		std::unique_ptr<AnimationNode> m_anyNode;

		std::vector<std::unique_ptr<AnimationNode>> m_animations;
	public:
		Animator(GameObject* obj, SDL_Renderer* renderer, Vector3f anchor = { 0, 0, 0 });
		void OnStart();
		void OnIterate();
		void OnDraw(SDL_Renderer* renderer);
		std::unique_ptr<Component> copy();

		AnimationNode* AddAnimation(AnimationNode* prevNode, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect, int num_frame, cond_func* cond, float delay);
		AnimationNode* AddAnimation(AnimationNode* node);
		AnimationNode* CopyAnyNode(AnimationNode* node);
		AnimationNode* GetAnyNode();
		void SetStartNode(AnimationNode* node);
		SDL_FRect GetDstRect() const;
};

#endif
