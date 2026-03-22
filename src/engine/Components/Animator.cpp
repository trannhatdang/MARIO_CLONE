#include "engine/Components/Animator.h"

Animator::Animator(GameObject* obj, SDL_Renderer* renderer, Vector3f anchor) : Component("Animator", obj), m_renderer(renderer), m_anchor(anchor)
{
	m_anyNode = std::make_unique<AnimationNode>();
}

void Animator::OnStart()
{
	if(m_startNode)
	{
		m_currNode = m_startNode;
	}
	else
	{
		m_currNode = m_anyNode->adj[0];
	}
}

void Animator::OnIterate()
{
	for(auto i = 0; i < m_anyNode->conds.size(); ++i)
	{
		if(!m_anyNode->conds[i])
		{
			continue;
		}

		if(m_anyNode->conds[i](this->gameObject))
		{
			m_currNode = m_anyNode->adj[i];
			//m_currNode->anim->m_timeSinceLastAnim = 0.0f;
			return;
		}
	}

	if(!m_currNode) return;

	m_currNode->anim->m_timeSinceLastAnim += DGTime_deltaTime();

	for(auto i = 0; i < m_currNode->conds.size(); ++i)
	{
		if(!m_currNode->conds[i])
		{
			continue;
		}

		if(m_currNode->conds[i](this->gameObject))
		{
			m_currNode = m_currNode->adj[i];
			return;
		}
	}
}

void Animator::OnDraw(SDL_Renderer* renderer)
{
	auto pos = gameObject->GetTransform()->GetPosition();

	if(m_currNode)
	{
		int w = (int)m_currNode->anim->m_dstrect.w;
		int h = (int)m_currNode->anim->m_dstrect.h;
		m_currNode->anim->OnDraw(renderer, { pos.x - (int)(m_anchor.x * w), pos.y - (int)(m_anchor.y * h), w, h });
	}
}	

AnimationNode* Animator::AddAnimation(AnimationNode* prevNode, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect, int num_frame, cond_func* cond, float delay)
{
	AnimationNode* node = new AnimationNode;
	node->anim = std::make_unique<Animation>(m_renderer, filepath, srcrect, dstrect, num_frame, delay);

	if(prevNode)
	{
		prevNode->adj.push_back(node);
		prevNode->conds.push_back(cond);
	}
	else
	{
		m_anyNode->adj.push_back(node);
		m_anyNode->conds.push_back(cond);
	}

	m_animations.emplace_back(node);

	return node;
}

AnimationNode* Animator::AddAnimation(AnimationNode* node)
{
	return this->AddAnimation(nullptr, node->anim->m_filepath, node->anim->m_srcrect, node->anim->m_dstrect, node->anim->m_num_frames, nullptr, node->anim->m_delay);
}

AnimationNode* Animator::CopyAnyNode(AnimationNode* node)
{
	return nullptr;
}

AnimationNode* Animator::GetAnyNode()
{
	return m_anyNode.get();
}

void Animator::SetStartNode(AnimationNode* node)
{
	m_startNode = node;
};

SDL_FRect Animator::GetDstRect() const
{
	return m_currNode->anim->GetDstRect();
}

//I WILL NEVER COPY

std::unique_ptr<Component> Animator::copy()
{
	return nullptr;
	Animator* anim = new Animator(gameObject, m_renderer);

	anim->CopyAnyNode(m_anyNode.get());
	return std::unique_ptr<Animator>(anim);
}
