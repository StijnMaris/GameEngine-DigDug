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
}

dae::MovementComponent::~MovementComponent()
{
}

void dae::MovementComponent::MoveUp(std::shared_ptr<GridSystem> grid)
{
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), Direction::Up)
		&& static_cast<int> (m_pTransform->GetPosition().x + m_Rect.w / 2) % m_GridMovConstraintW <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x, m_pTransform->GetPosition().y - 32, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(gridPos.first, --gridPos.second);
		m_IsDestinationSet = true;
	}
}

void dae::MovementComponent::MoveDown(std::shared_ptr<GridSystem> grid)
{
	float pos = m_pTransform->GetPosition().x + m_Rect.w / 2;
	int mod = static_cast<int> (pos) % m_GridMovConstraintW;
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), Direction::Down)
		&& mod <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x, m_pTransform->GetPosition().y + 32, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(gridPos.first, ++gridPos.second);
		m_IsDestinationSet = true;
	}
}

void dae::MovementComponent::MoveLeft(std::shared_ptr<GridSystem> grid)
{
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), Direction::Left)
		&& static_cast<int> (m_pTransform->GetPosition().y + m_Rect.h / 2) % m_GridMovConstraintH <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x - 32, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(--gridPos.first, gridPos.second);
		m_IsDestinationSet = true;
	}
}

void dae::MovementComponent::MoveRight(std::shared_ptr<GridSystem> grid)
{
	if (grid->CanMoveInDirection(m_pTransform->GetPosition(), Direction::Right)
		&& static_cast<int> (m_pTransform->GetPosition().y + m_Rect.h / 2) % m_GridMovConstraintH <= 0)
	{
		//m_pTransform->SetPosition(m_pTransform->GetPosition().x + 32, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z);
		m_StartPos = m_pTransform->GetPosition();
		std::pair<int, int> gridPos = grid->GetCellData(m_pTransform->GetPosition());
		m_Destination = grid->GetCellPosition(++gridPos.first, gridPos.second);
		m_IsDestinationSet = true;
	}
}

void dae::MovementComponent::Update()
{
	if (m_IsDestinationSet) {
		auto& time = Time::GetInstance();
		time.GetDeltaTime();
		m_pTransform->SetPosition(glm::mix(m_pTransform->GetPosition(), m_Destination, 0.1f));
		glm::vec3 posSub = m_Destination - m_pTransform->GetPosition();
		posSub = abs(posSub);
		if (posSub.x <= 1 && posSub.y <= 1)
		{
			m_pTransform->SetPosition(m_Destination);
		}
	}
}