#include "MiniginPCH.h"
#include "Character.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "CommandComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "ActionComponent.h"

dae::Character::Character(std::string name, std::string imagePath, int rows, int cols, int startRow) :
	m_Name(name), m_PathName(imagePath), m_Rows(rows), m_Cols(cols), m_StartRow(startRow)
{
	m_pCharacter = std::make_shared<GameObject>(m_Name);
}

void dae::Character::Init()
{
	m_pCharacter->Init();
	m_pCharacter->SetScale(2, 2);
	m_pCharacter->AddComponent(std::make_shared<TextureComponent>(m_PathName));
	m_pCharacter->AddComponent(std::make_shared<SpriteComponent>(m_pCharacter->GetComponent<TextureComponent>(), m_Rows, m_Cols, m_StartRow, true, 200));
	m_pCharacter->AddComponent(std::make_shared<RenderComponent>(m_pCharacter->GetComponent<SpriteComponent>()));
	m_pCharacter->AddComponent(std::make_shared<CommandComponent>());
	m_pCharacter->AddComponent(std::make_shared<ActionComponent>(m_pCharacter->GetComponent<Transform>()));
	m_pCharacter->AddComponent(std::make_shared<ColliderComponent>(m_pCharacter->GetComponent<Transform>(), m_pCharacter->GetComponent<SpriteComponent>()->GetRectToDraw()));
	m_pCharacter->AddComponent(std::make_shared<MovementComponent>(m_pCharacter->GetComponent<Transform>(), m_pCharacter->GetComponent<ColliderComponent>()->GetCollider(), 0.1f));
}

void dae::Character::Update()
{
	switch (m_CharacterState)
	{
	case CharacterState::Idle:
		m_pCharacter->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(CharacterState::Idle));
		break;
	case CharacterState::Action:
		m_pCharacter->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(CharacterState::Action));
		break;
	case CharacterState::Die:
		m_pCharacter->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(CharacterState::Die));
		break;
	default:
		m_pCharacter->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(CharacterState::Idle));
		break;
	}
}

void dae::Character::Die()
{
	SetCharacterState(CharacterState::Die);
}

void dae::Character::SetPosition(glm::vec3 newPos)const
{
	m_pCharacter->SetPosition(newPos);
	m_pCharacter->GetComponent<MovementComponent>()->SetPosition(newPos);
}