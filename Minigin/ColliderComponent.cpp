#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"

dae::ColliderComponent::ColliderComponent() :BaseComponent("ColliderComponent")
{
	m_pTransformComponent = GetOwner()->GetComponent<Transform>();
}

dae::ColliderComponent::~ColliderComponent()
{
}

void dae::ColliderComponent::Update()
{
	m_PrevPosition = m_pTransformComponent->GetPosition();
}