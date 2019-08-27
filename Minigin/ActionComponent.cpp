#include "MiniginPCH.h"
#include "ActionComponent.h"
#include "GridSystem.h"
#include "Transform.h"
#include "GridBlock.h"
#include "Character.h"
#include "LevelScene.h"

dae::ActionComponent::ActionComponent(std::shared_ptr<Transform> transform) :BaseComponent("ActionComponent"), m_pTransform(transform)
{
	m_Destination = glm::vec3{};
	m_StartPos = glm::vec3{};
}

void dae::ActionComponent::DoAction(std::shared_ptr<LevelScene> level, MovementDirection movDir)
{
	const std::pair<int, int> neighborGridPos = level->GetGridSystem()->GetNeighboringBlockInDirection(m_pTransform->GetPosition(), movDir);
	const glm::vec3 neighborPos = level->GetGridSystem()->GetCellPosition(neighborGridPos);
	if (neighborGridPos.first >= 0 && neighborGridPos.second >= 0)
	{
		BlockColor color = level->GetGridSystem()->GetGridBlockAtPosition(neighborGridPos)->GetBlockColor();
		if (color == BlockColor::Wall)
		{
		}
		else if (level->GetIsMultyPlayer()  && !level->GetGridSystem()->GetPlayer("Player2")->GetIsFriendly())
		{
			level->GetGridSystem()->DestroyBlock(neighborGridPos.first, neighborGridPos.second);
		}
		else {
			if (!level->GetGridSystem()->CanMoveInDirection(m_pTransform->GetPosition(), movDir) && !level->GetGridSystem()->CanMoveInDirection(neighborPos, movDir) && color != BlockColor::Diamond)
			{
				level->GetGridSystem()->DestroyBlock(neighborGridPos.first, neighborGridPos.second);
			}
			else if (!level->GetGridSystem()->CanMoveInDirection(m_pTransform->GetPosition(), movDir) && level->GetGridSystem()->CanMoveInDirection(neighborPos, movDir))
			{
				level->GetGridSystem()->SlideBlockInDirection(neighborPos, movDir, color);
			}
		}
	}
}