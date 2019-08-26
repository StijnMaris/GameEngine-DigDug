#include "MiniginPCH.h"
#include "LevelScene.h"
//#include "SceneManager.h"
#include "Time.h"
#include "GameObject.h"
#include "Character.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "CommandComponent.h"
//#include "ColliderComponent.h"
//#include "GridBlock.h"
//#include "Renderer.h"
#include "GridSystem.h"
#include "Observer.h"

void dae::LevelScene::Init()
{
	auto& time = Time::GetInstance();

	/*std::shared_ptr<GameObject> go = std::make_shared<GameObject>("BackGround");
	go->Init();
	go->AddComponent(std::make_shared<TextureComponent>("background.jpg"));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<TextureComponent>()));
	go->SetPosition(0, 0);
	AddGameObject(go);*/

	m_pTheGrid = std::make_shared<GridSystem>(21, 19, m_FilePath, shared_from_this());
	m_pTheGrid->GetGridSystem()->Init();
	m_pTheGrid->GetGridSystem()->SetPosition(16, 16 + 32 * 4);
	m_pTheGrid->Init();
	std::shared_ptr<Score> scoreObserver = std::make_shared<Score>();
	m_pTheGrid->addObserver(scoreObserver);

	InitPlayer1Controles(m_pTheGrid->GetPlayer());
	AddGameObject(m_pTheGrid->GetPlayer()->GetCharacter());

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("TitleText");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("PENGO", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(220, 20);
	AddGameObject(to);

	m_Score = std::make_shared<GameObject>("Score");
	m_Score->Init();
	m_Score->AddComponent(std::make_shared<TextComponent>("Score: 0", font));
	m_Score->AddComponent(std::make_shared<RenderComponent>(m_Score->GetComponent<TextComponent>()->GetTextureComponent()));
	m_Score->SetPosition(220, 60);
	AddGameObject(m_Score);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	to = std::make_shared<GameObject>("FPSText");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("FPS:", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(550, 10);
	AddGameObject(to);

	to = std::make_shared<GameObject>("FPS");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>(std::to_string(time.GetFps()), font));
	to->AddComponent(std::make_shared<FPSComponent>(to->GetComponent<TextComponent>()));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(590, 10);
	AddGameObject(to);
}

void dae::LevelScene::Update()
{
	Scene::Update();
	m_pTheGrid->Update();
	m_pTheGrid->CheckForCollision();
	m_Score->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(Score::m_Score));
}

void dae::LevelScene::Render() const
{
	Scene::Render();
	m_pTheGrid->Draw();
}

void dae::LevelScene::InitPlayer1Controles(std::shared_ptr<Character> gameObject)
{
	auto& input = InputManager::GetInstance();
	const InputAction LeftRun = { 1,InputTriggerState::Down,SDL_SCANCODE_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT };
	input.MapInput(LeftRun, std::make_shared<RunLeftCommand>(gameObject, shared_from_this()));
	const InputAction RightRun = { 2,InputTriggerState::Down,SDL_SCANCODE_RIGHT,-1,XINPUT_GAMEPAD_DPAD_RIGHT };
	input.MapInput(RightRun, std::make_shared<RunRightCommand>(gameObject, shared_from_this()));
	const InputAction UpRun = { 3,InputTriggerState::Down,SDL_SCANCODE_UP,-1,XINPUT_GAMEPAD_DPAD_UP };
	input.MapInput(UpRun, std::make_shared<RunUpCommand>(gameObject, shared_from_this()));
	const InputAction DownRun = { 4,InputTriggerState::Down,SDL_SCANCODE_DOWN,-1,XINPUT_GAMEPAD_DPAD_DOWN };
	input.MapInput(DownRun, std::make_shared<RunDownCommand>(gameObject, shared_from_this()));

	const InputAction Push = { 5,InputTriggerState::Pressed,SDL_SCANCODE_SPACE,-1,XINPUT_GAMEPAD_A };
	input.MapInput(Push, std::make_shared<ActionCommand>(gameObject, shared_from_this()));

	InputAction Reset = { 6,InputTriggerState::Pressed,SDL_SCANCODE_R,-1,XINPUT_GAMEPAD_BACK };
	input.MapInput(Reset, std::make_shared<ResetCommand>(gameObject, shared_from_this()));

	const InputAction Exit = { 16,InputTriggerState::Pressed,SDL_SCANCODE_ESCAPE,-1,XINPUT_GAMEPAD_START };
	input.MapInput(Exit, std::make_shared<ExitCommand>(gameObject, shared_from_this()));
}

void dae::LevelScene::Reset()
{
	m_pTheGrid->Reset();
	//Init();
}

dae::LevelScene::LevelScene(const std::string& name, const std::string& LevelFile) :Scene(name), m_FilePath(LevelFile)
{
}

dae::LevelScene::~LevelScene() = default;