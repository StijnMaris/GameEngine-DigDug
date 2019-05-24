#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"

dae::ColliderComponent::ColliderComponent(std::shared_ptr<Transform> transform, int width, int height) :BaseComponent("ColliderComponent"), m_pTransformComponent(transform)
{
	SetColliderRect(m_pTransformComponent->GetPosition(), width, height);
}

dae::ColliderComponent::~ColliderComponent()
{
}

void dae::ColliderComponent::Update()
{
	m_PrevPosition = m_pTransformComponent->GetPosition();
}

void dae::ColliderComponent::SetColliderRect(glm::vec3 pos, int width, int height)
{
	m_Collider.w = width;
	m_Collider.h = height;
	//TODO 1: find out the problem with vec2
	m_Collider.x = (int)pos.x;
	m_Collider.y = (int)pos.y;
}