#include "MiniginPCH.h"
#include "MenuButton.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#include "CommandComponent.h"
#include "ButtonComponent.h"
//#include "ResourceManager.h"
//#include "TextComponent.h"

dae::MenuButton::MenuButton(std::string& name, std::string& file, std::string& levelName) :m_ButtonState(ButtonState::Idle), m_PathName(file), m_LevelPathName(levelName)
{
	m_pButton = std::make_shared<GameObject>(name);
	//m_ButtonState = ButtonState::Pressed;
}

dae::MenuButton::~MenuButton()
{
}

void dae::MenuButton::Init()
{
	m_pButton->Init();
	m_pButton->AddComponent(std::make_shared<TextureComponent>(m_PathName));
	m_pButton->AddComponent(std::make_shared<SpriteComponent>(m_pButton->GetComponent<TextureComponent>(), 3, 1));
	m_pButton->AddComponent(std::make_shared<RenderComponent>(m_pButton->GetComponent<SpriteComponent>()));
	m_pButton->AddComponent(std::make_shared<ButtonComponent>());
}

void dae::MenuButton::Update()
{
	switch (m_ButtonState)
	{
	case ButtonState::Idle:
		m_pButton->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(ButtonState::Idle));
		break;
	case ButtonState::Highlighted:
		m_pButton->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(ButtonState::Highlighted));
		break;
	case ButtonState::Pressed:
		m_pButton->GetComponent<SpriteComponent>()->SetStartRow(static_cast<int>(ButtonState::Pressed));
		break;
	}
}