#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "Transform.h"

dae::MovementComponent::MovementComponent(std::shared_ptr<Transform> transform, SDL_Rect rect) :
	BaseComponent("MovementComponent"), m_pTransform(transform), m_Rect(rect)
{
}

dae::MovementComponent::~MovementComponent()
{
}

void dae::MovementComponent::MoveUp()
{
	auto newY = m_pTransform->GetPosition().y - m_Rect.h;
	if (newY > 128)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition().x, newY, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::MoveDown()
{
	auto newY = m_pTransform->GetPosition().y + m_Rect.h;
	if (newY < 796)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition().x, newY, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::MoveLeft()
{
	auto newX = m_pTransform->GetPosition().x - m_Rect.w;
	if (newX > 0)
	{
		m_pTransform->SetPosition(newX, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::MoveRight()
{
	auto newX = m_pTransform->GetPosition().x + m_Rect.w;
	if (newX < 640)
	{
		m_pTransform->SetPosition(newX, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::Update()
{
}