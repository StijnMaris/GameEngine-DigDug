#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "GridSystem.h"
#include <cmath>
#include "Time.h"

dae::MovementComponent::MovementComponent(std::shared_ptr<Transform> transform, SDL_Rect rect) :
	BaseComponent("MovementComponent"), m_pTransform(transform), m_Rect(rect)
{
	m_GridMovConstraintW = m_Rect.w;
	m_GridMovConstraintH = m_Rect.h;
	m_IsDestinationSet = false;
	m_Destination = glm::vec3{};
	m_StartPos = glm::vec3{};
}

void dae::MovementComponent::MoveUp(std::shared_ptr<GridSystem> grid)
{
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), MovementDirection::Up)
		&& static_cast<int> (m_pTransform->GetPosition().x + m_Rect.w / 2) % m_GridMovConstraintW <= 0)
	{
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(--gridPos.first, gridPos.second);
	}
}

void dae::MovementComponent::MoveDown(std::shared_ptr<GridSystem> grid)
{
	float pos = m_pTransform->GetPosition().x + m_Rect.w / 2;
	int mod = static_cast<int> (pos) % m_GridMovConstraintW;
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), MovementDirection::Down)
		&& mod <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x, m_pTransform->GetPosition().y + 32, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(++gridPos.first, gridPos.second);
	}
}

void dae::MovementComponent::MoveLeft(std::shared_ptr<GridSystem> grid)
{
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), MovementDirection::Left)
		&& static_cast<int> (m_pTransform->GetPosition().y + m_Rect.h / 2) % m_GridMovConstraintH <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x - 32, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(gridPos.first, --gridPos.second);
	}
}

void dae::MovementComponent::MoveRight(std::shared_ptr<GridSystem> grid)
{
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), MovementDirection::Right)
		&& static_cast<int> (m_pTransform->GetPosition().y + m_Rect.h / 2) % m_GridMovConstraintH <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x + 32, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(gridPos.first, ++gridPos.second);
	}
}

void dae::MovementComponent::Update()
{
	auto& time = Time::GetInstance();
	time.GetDeltaTime();
	m_pTransform->SetPosition(glm::mix(m_pTransform->GetPosition(), m_Destination, 0.1f));
	glm::vec3 posSub = m_Destination - m_pTransform->GetPosition();
	posSub = abs(posSub);
	if (posSub.x <= 5 && posSub.y <= 5)
	{
		m_pTransform->SetPosition(m_Destination);
	}
}

void dae::MovementComponent::SetPosition(glm::vec3 newPos)
{
	m_StartPos = newPos;
	m_Destination = newPos;
}