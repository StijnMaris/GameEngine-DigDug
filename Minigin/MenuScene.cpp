#include "MiniginPCH.h"
#include "MenuScene.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "InputManager.h"
#include "CommandComponent.h"

dae::MenuScene::MenuScene(const std::string& name) :Scene(name)
{
	m_BackGroundPos = { 224,288 };
	m_ButtonPos = { 75,550 };
	m_NeedsUpdate = false;
	m_Names.push_back("BSinglePlayer");
	m_Names.push_back("MenuButtonSP.png");
	m_Names.push_back("Level1SP");
	m_Names.push_back("BMultyPlayer");
	m_Names.push_back("MenuButtonMP.png");
	m_Names.push_back("Level1MP");
	m_Names.push_back("BVSPlayer");
	m_Names.push_back("MenuButtonVSP.png");
	m_Names.push_back("Level1VSP");
}

void dae::MenuScene::Init()
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("Background");
	go->Init();
	go->SetScale(2.f, 2.f, 0);
	go->AddComponent(std::make_shared<TextureComponent>("Pengo_Menu.png"));
	go->AddComponent(std::make_shared<SpriteComponent>(go->GetComponent<TextureComponent>(), 1, 1));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<SpriteComponent>()));
	go->SetPosition(m_BackGroundPos.x* 1.4f, m_BackGroundPos.y + 10);
	AddGameObject(go);

	m_pMenu = std::make_shared<GameObject>("Menu");
	m_pMenu->Init();
	m_pMenu->AddComponent(std::make_shared<CommandComponent>());
	AddGameObject(go);

	for (int i = 0; i < m_Names.size() / 3.f; ++i)
	{
		auto button = std::make_shared<MenuButton>(m_Names[i * 3], m_Names[i * 3 + 1], m_Names[i * 3 + 2]);
		button->Init();
		button->GetButton()->SetPosition(m_BackGroundPos.x + m_BackGroundPos.x / 2.5f, m_BackGroundPos.y * (2.f + i * 0.25f));
		if (i == 0)
		{
			button->SetButtonState(ButtonState::Highlighted);
		}
		m_pButtons.push_back(button);
		AddGameObject(button->GetButton());
	}

	InitMenuControls();
}

void dae::MenuScene::Update()
{
	Scene::Update();
	m_pMenu->Update();
	for (std::shared_ptr<MenuButton> element : m_pButtons)
	{
		element->Update();
	}
}

void dae::MenuScene::Render() const
{
	Scene::Render();
}

void dae::MenuScene::InitMenuControls()
{
	auto& input = InputManager::GetInstance();
	std::string name = "MenuButtonUp";
	const InputAction ButtonUp = { name,InputTriggerState::Pressed,SDL_SCANCODE_UP,-1,XINPUT_GAMEPAD_DPAD_UP  };
	input.MapInput(ButtonUp, std::make_shared<MenuButtonUp>(GetMenu(), GetMenuButtons()));
	name = "MenuButtonDown";
	const InputAction ButtonDown = { name,InputTriggerState::Pressed,SDL_SCANCODE_DOWN,-1,XINPUT_GAMEPAD_DPAD_DOWN };
	input.MapInput(ButtonDown, std::make_shared<MenuButtonDown>(GetMenu(), GetMenuButtons()));
	name = "MenuButtonSelect";
	const InputAction MenuButtonSelect = { name,InputTriggerState::Pressed,SDL_SCANCODE_SPACE,-1,XINPUT_GAMEPAD_A  };
	input.MapInput(MenuButtonSelect, std::make_shared<MenuButtonPress>(GetMenu(), GetMenuButtons()));
}