#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"

dae::ColliderComponent::ColliderComponent(std::shared_ptr<Transform> transform, SDL_Rect rect) :BaseComponent("ColliderComponent"), m_pTransformComponent(transform)
{
	SetColliderRect(rect);
}

dae::ColliderComponent::~ColliderComponent()
{
}

void dae::ColliderComponent::Update()
{
	m_PrevPosition = m_pTransformComponent->GetPosition();
	m_Collider.x = static_cast<int> (m_pTransformComponent->GetPosition().x);
	m_Collider.y = static_cast<int> (m_pTransformComponent->GetPosition().y);
}

void dae::ColliderComponent::SetColliderRect(SDL_Rect rect)
{
	m_Collider = rect;
	m_Collider.w = int(static_cast<float>(m_Collider.w) * m_pTransformComponent->GetScale().x);
	m_Collider.h = int(static_cast<float>(m_Collider.h) * m_pTransformComponent->GetScale().y);
	m_Collider.x = static_cast<int> (m_pTransformComponent->GetPosition().x);
	m_Collider.y = static_cast<int> (m_pTransformComponent->GetPosition().y);
	m_Collider.x -= int(m_Collider.w * 0.5f);
	m_Collider.y -= int(m_Collider.h * 0.5f);
}