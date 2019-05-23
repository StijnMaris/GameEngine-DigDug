#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"

dae::ColliderComponent::ColliderComponent(glm::vec2 pos, int width, int height) :BaseComponent("ColliderComponent")
{
	SetColliderRect(pos, width, height);
	m_pTransformComponent = GetOwner()->GetComponent<Transform>();
}

dae::ColliderComponent::~ColliderComponent()
{
}

void dae::ColliderComponent::Update()
{
	m_PrevPosition = m_pTransformComponent->GetPosition();
}

void dae::ColliderComponent::SetColliderRect(glm::vec2 pos, int width, int height)
{
	m_Collider.w = width;
	m_Collider.h = height;
	//TODO 1: find out the problem with vec2
	m_Collider.x = (int)pos.x;
	m_Collider.y = (int)pos.y;
}