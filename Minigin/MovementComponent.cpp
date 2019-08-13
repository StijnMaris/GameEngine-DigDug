#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "Transform.h"

dae::MovementComponent::MovementComponent(std::shared_ptr<Transform> transform, SDL_Rect rect) :
	BaseComponent("MovementComponent"), m_pTransform(transform), m_Rect(rect)
{
	m_BoundRect = SDL_Rect{ 8,136,632,788 };
	m_MovementsizeH = m_Rect.h / 4.f;
	m_MovementsizeW = m_Rect.w / 4.f;
	m_GridMovConstraintW = m_Rect.w;
	m_GridMovConstraintH = m_Rect.h;
}

dae::MovementComponent::~MovementComponent()
{
}

void dae::MovementComponent::MoveUp()
{
	auto newY = m_pTransform->GetPosition().y - m_MovementsizeH;
	if (newY > m_BoundRect.y && static_cast<int> (m_pTransform->GetPosition().x + m_Rect.w / 2) % m_GridMovConstraintW == 0)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition().x, newY, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::MoveDown()
{
	auto newY = m_pTransform->GetPosition().y + m_MovementsizeH;
	if (newY < m_BoundRect.h && static_cast<int> (m_pTransform->GetPosition().x + m_Rect.w / 2) % m_GridMovConstraintW == 0)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition().x, newY, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::MoveLeft()
{
	auto newX = m_pTransform->GetPosition().x - m_MovementsizeW;
	if (newX > m_BoundRect.x && static_cast<int> (m_pTransform->GetPosition().y + m_Rect.h / 2) % m_GridMovConstraintH == 0)
	{
		m_pTransform->SetPosition(newX, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::MoveRight()
{
	auto newX = m_pTransform->GetPosition().x + m_MovementsizeW;
	if (newX < m_BoundRect.w && static_cast<int> (m_pTransform->GetPosition().y + m_Rect.h / 2) % m_GridMovConstraintH == 0)
	{
		m_pTransform->SetPosition(newX, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
	}
}

void dae::MovementComponent::Update()
{
}