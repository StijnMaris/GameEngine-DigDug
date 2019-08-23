#include "MiniginPCH.h"
#include "SlidingBlock.h"
#include "GridBlock.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"

dae::SlidingBlock::SlidingBlock(glm::vec3 pos, dae::MovementDirection movDir, int row, int col, dae::BlockColor color, bool destroyed) :GridBlock(pos, row, col, color, destroyed), m_MovementDirection(movDir)
{
}

dae::SlidingBlock::~SlidingBlock()
{
}

void dae::SlidingBlock::Init()
{
	GridBlock::Init();
	GetBlock()->AddComponent(std::make_shared<dae::MovementComponent>(GetBlock()->GetComponent<dae::Transform>(), GetBlock()->GetComponent<dae::ColliderComponent>()->GetCollider(), 0.5f));
	GetBlock()->GetComponent<MovementComponent>()->SetPosition(GetBlock()->GetPosition());
}