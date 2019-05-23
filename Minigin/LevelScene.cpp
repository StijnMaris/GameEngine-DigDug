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

dae::LevelScene::LevelScene()
{
}

void dae::LevelScene::Init()
{
	InitControles();
	auto& scene = SceneManager::GetInstance().CreateScene("Level");
	auto& time = Time::GetInstance();

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("BackGround");
	go->Init();
	go->AddComponent(std::make_shared<TextureComponent>("background.jpg"));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<TextureComponent>()));
	go->SetPosition(0, 0);
	scene.AddGameObject(go);

	go = std::make_shared<GameObject>("DAELogo");
	go->Init();
	go->SetPosition(216, 180);
	go->AddComponent(std::make_shared<TextureComponent>("logo.png"));
	go->AddComponent(std::make_shared<SpriteComponent>(go->GetComponent<TextureComponent>(), glm::vec2{ 100,100 }));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<SpriteComponent>()));
	go->AddComponent(std::make_shared<CommandComponent>());

	scene.AddGameObject(go);
	auto& input = InputManager::GetInstance();
	InputAction LeftRun = { XINPUT_GAMEPAD_DPAD_LEFT,InputTriggerState::Pressed,VK_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT };
	input.MapInput(LeftRun, std::make_shared<RunLeftCommand>(go));
	InputAction RightRun = { XINPUT_GAMEPAD_DPAD_RIGHT,InputTriggerState::Pressed,VK_RIGHT,-1,XINPUT_GAMEPAD_DPAD_RIGHT };
	input.MapInput(RightRun, std::make_shared<RunRightCommand>(go));
	InputAction UpRun = { XINPUT_GAMEPAD_DPAD_UP,InputTriggerState::Pressed,VK_UP,-1,XINPUT_GAMEPAD_DPAD_UP };
	input.MapInput(UpRun, std::make_shared<RunUpCommand>(go));
	InputAction DownRun = { XINPUT_GAMEPAD_DPAD_DOWN,InputTriggerState::Pressed,VK_DOWN,-1,XINPUT_GAMEPAD_DPAD_DOWN };
	input.MapInput(DownRun, std::make_shared<RunDownCommand>(go));
	InputAction Exit = { XINPUT_GAMEPAD_START,InputTriggerState::Pressed,VK_ESCAPE,-1,XINPUT_GAMEPAD_START };
	input.MapInput(Exit, std::make_shared<ExitCommand>(go));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("TitleText");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(80, 20);
	scene.AddGameObject(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	to = std::make_shared<GameObject>("FPSText");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("FPS:", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(570, 10);
	scene.AddGameObject(to);

	to = std::make_shared<GameObject>("FPS");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>(std::to_string(time.GetFps()), font));
	to->AddComponent(std::make_shared<FPSComponent>(to->GetComponent<TextComponent>()));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(610, 10);
	scene.AddGameObject(to);
}

void dae::LevelScene::InitControles()
{
	//InputAction RightRun = { XINPUT_GAMEPAD_DPAD_LEFT,InputTriggerState::Down,VK_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT };
	//InputAction UpRun = { XINPUT_GAMEPAD_DPAD_LEFT,InputTriggerState::Released,VK_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT };

	//MapInput(RightRun, std::make_shared<RunLeftCommand>());
	//MapInput(UpRun, std::make_shared<RunLeftCommand>());
	//m_pButtons.insert_or_assign(VK_UP, std::make_shared<RunUpCommand>());
	//m_pButtons.insert_or_assign(XINPUT_GAMEPAD_DPAD_LEFT, std::make_shared<RunLeftCommand>());
	//m_pButtons.insert_or_assign(XINPUT_GAMEPAD_DPAD_UP, std::make_shared<RunDownCommand>());
	//m_pButtons.insert_or_assign(ControllerButton::L1, std::make_shared<ExitCommand>());
	//m_pButtons.insert_or_assign(XINPUT_GAMEPAD_START, std::make_shared<ExitCommand>());
}