#include "MiniginPCH.h"
#include "GridBlock.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"

dae::GridBlock::GridBlock(glm::vec3 pos, int row, int col, BlockColor color, bool hasCollision, bool destroyed) :
	m_Pos(pos), m_Row(row), m_Col(col), m_Color(color), m_Destroyed(destroyed), m_HasCollision(hasCollision)
{
	m_pBlock = std::make_shared<GameObject>("GridBlock");
}

dae::GridBlock::~GridBlock()
{
}

void dae::GridBlock::Init()
{
	m_pBlock->Init();
	m_pBlock->SetPosition(m_Pos);
	m_pBlock->AddComponent(std::make_shared<TextureComponent>("Ground.png"));
	m_pBlock->AddComponent(std::make_shared<SpriteComponent>(m_pBlock->GetComponent<TextureComponent>(), m_Row, m_Col, static_cast<int>(m_Color)));
	m_pBlock->AddComponent(std::make_shared<RenderComponent>(m_pBlock->GetComponent<SpriteComponent>()));
	m_pBlock->AddComponent(std::make_shared<ColliderComponent>(m_pBlock->GetComponent<Transform>(), m_pBlock->GetComponent<SpriteComponent>()->GetRectToDraw()));
}

bool dae::GridBlock::Destroy()
{
	if (m_Destroyed)
	{
		//m_pBlock->Destroy();
		return true;
	}
	return false;
}