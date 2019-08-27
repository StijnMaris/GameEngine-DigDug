#include "MiniginPCH.h"
#include "ActionComponent.h"
#include "GridSystem.h"
#include "Transform.h"
#include "GridBlock.h"

dae::ActionComponent::ActionComponent(std::shared_ptr<Transform> transform) :BaseComponent("ActionComponent"), m_pTransform(transform)
{
	m_Destination = glm::vec3{};
	m_StartPos = glm::vec3{};
}

void dae::ActionComponent::DoAction(std::shared_ptr<GridSystem> grid, MovementDirection movDir)
{
	const std::pair<int, int> neighborGridPos = grid->GetNeighboringBlockInDirection(m_pTransform->GetPosition(), movDir);
	const glm::vec3 neighborPos = grid->GetCellPosition(neighborGridPos);
	if (neighborGridPos.first >= 0 && neighborGridPos.second >= 0)
	{
		BlockColor color = grid->GetGridBlockAtPosition(neighborGridPos)->GetBlockColor();
		if (color == BlockColor::Wall)
		{
		}
		else if (!grid->CanMoveInDirection(m_pTransform->GetPosition(), movDir) && !grid->CanMoveInDirection(neighborPos, movDir) && color != BlockColor::Diamond)
		{
			grid->DestroyBlock(neighborGridPos.first, neighborGridPos.second);
		}
		else if (!grid->CanMoveInDirection(m_pTransform->GetPosition(), movDir) && grid->CanMoveInDirection(neighborPos, movDir))
		{
			grid->SlideBlockInDirection(neighborPos, movDir, color);
		}
	}
}