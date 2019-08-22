#include "MiniginPCH.h"
#include "ActionComponent.h"
#include "GridSystem.h"
#include "Transform.h"
#include "GridBlock.h"

dae::ActionComponent::ActionComponent(std::shared_ptr<Transform> transform) :BaseComponent("ActionComponent"), m_pTransform(transform)
{
}

void dae::ActionComponent::DoAction(std::shared_ptr<GridSystem> grid, MovementDirection movDir)
{
	std::pair<int, int> neighborPos = grid->GetNeighboringBlockInDirection(m_pTransform->GetPosition(), movDir);
	if (neighborPos.first >= 0 && neighborPos.second >= 0)
	{
		if (!grid->CanMoveInDirection(m_pTransform->GetPosition(), movDir) && !grid->CanMoveInDirection(grid->GetCellPosition(neighborPos), movDir) && grid->GetGridBlockAtPosition(neighborPos)->GetBlockColor() != BlockColor::Diamond)
		{
			grid->DestroyCell(neighborPos.first, neighborPos.second);
		}
		else if (!grid->CanMoveInDirection(m_pTransform->GetPosition(), movDir) && grid->CanMoveInDirection(grid->GetCellPosition(neighborPos), movDir))
		{
			grid->GetGridBlockAtPosition(neighborPos);
		}
	}
}