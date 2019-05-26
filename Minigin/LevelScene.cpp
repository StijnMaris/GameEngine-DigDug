#include "MiniginPCH.h"
#include "LevelScene.h"
#include "SceneManager.h"
#include "Time.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "CommandComponent.h"
#include "ColliderComponent.h"
#include "GridBlock.h"
#include "Renderer.h"
#include "GridSystem.h"
#include "Player.h"

void dae::LevelScene::Init()
{
	auto& time = Time::GetInstance();

	/*std::shared_ptr<GameObject> go = std::make_shared<GameObject>("BackGround");
	go->Init();
	go->AddComponent(std::make_shared<TextureComponent>("background.jpg"));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<TextureComponent>()));
	go->SetPosition(0, 0);
	AddGameObject(go);*/

	m_pTheGrid = std::make_shared<GridSystem>(25, 20);
	m_pTheGrid->GetGridSystem()->Init();
	m_pTheGrid->GetGridSystem()->SetPosition(16, 16);
	m_pTheGrid->Init();
	m_pTheGrid->AddToScene(*this);

	InitPlayer1Controles(m_pTheGrid->GetPlayer()->GetCharacter());
	AddGameObject(m_pTheGrid->GetPlayer()->GetCharacter());

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("TitleText");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(80, 20);
	AddGameObject(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	to = std::make_shared<GameObject>("FPSText");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("FPS:", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(570, 10);
	AddGameObject(to);

	to = std::make_shared<GameObject>("FPS");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>(std::to_string(time.GetFps()), font));
	to->AddComponent(std::make_shared<FPSComponent>(to->GetComponent<TextComponent>()));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(610, 10);
	AddGameObject(to);
}

void dae::LevelScene::Update()
{
	Scene::Update();

	m_pTheGrid->CheckForCollision();
	/*auto test3 = test->GetComponent<ColliderComponent>()->GetCollider();
	if (test2->CheckIfColliding(test3))
	{
		test2->SetBlockColor(BlockColor::Black);
	}*/
}

void dae::LevelScene::Render() const
{
	Scene::Render();
	//m_pTheGrid->Draw();
}

void dae::LevelScene::InitPlayer1Controles(std::shared_ptr<GameObject> gameObject)
{
	auto& input = InputManager::GetInstance();
	InputAction LeftRun = { XINPUT_GAMEPAD_DPAD_LEFT,InputTriggerState::Pressed,VK_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT };
	input.MapInput(LeftRun, std::make_shared<RunLeftCommand>(gameObject));
	InputAction RightRun = { XINPUT_GAMEPAD_DPAD_RIGHT,InputTriggerState::Pressed,VK_RIGHT,-1,XINPUT_GAMEPAD_DPAD_RIGHT };
	input.MapInput(RightRun, std::make_shared<RunRightCommand>(gameObject));
	InputAction UpRun = { XINPUT_GAMEPAD_DPAD_UP,InputTriggerState::Pressed,VK_UP,-1,XINPUT_GAMEPAD_DPAD_UP };
	input.MapInput(UpRun, std::make_shared<RunUpCommand>(gameObject));
	InputAction DownRun = { XINPUT_GAMEPAD_DPAD_DOWN,InputTriggerState::Pressed,VK_DOWN,-1,XINPUT_GAMEPAD_DPAD_DOWN };
	input.MapInput(DownRun, std::make_shared<RunDownCommand>(gameObject));
	InputAction Exit = { XINPUT_GAMEPAD_START,InputTriggerState::Pressed,VK_ESCAPE,-1,XINPUT_GAMEPAD_START };
	input.MapInput(Exit, std::make_shared<ExitCommand>(gameObject));
}

dae::LevelScene::LevelScene(const std::string& name) :Scene(name)
{
}