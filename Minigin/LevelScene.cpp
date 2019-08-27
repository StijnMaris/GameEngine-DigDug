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

	if (!(GetSceneName().compare("Level1MP")) || !(GetSceneName().compare("Level1VSP")))
	{
		m_IsMultyPlayer = true;
	}

	m_pTheGrid = std::make_shared<GridSystem>(21, 19, m_FilePath, shared_from_this());
	m_pTheGrid->GetGridSystem()->Init();
	m_pTheGrid->GetGridSystem()->SetPosition(16, 16 + 32 * 4);
	m_pTheGrid->Init();
	const std::shared_ptr<Score> scoreObserver = std::make_shared<Score>();
	m_pTheGrid->addObserver(scoreObserver);

	InitPlayer1Controles(m_pTheGrid->GetPlayer("Player1"));
	if (m_IsMultyPlayer)
	{
		InitPlayer2Controles(m_pTheGrid->GetPlayer("Player2"));
	}

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_pTitle = std::make_shared<GameObject>("TitleText");
	m_pTitle->Init();
	m_pTitle->AddComponent(std::make_shared<TextComponent>("DIGDUG ON ICE", font));
	m_pTitle->AddComponent(std::make_shared<RenderComponent>(m_pTitle->GetComponent<TextComponent>()->GetTextureComponent()));
	m_pTitle->SetPosition(220, 20);
	AddGameObject(m_pTitle);

	m_pScore = std::make_shared<GameObject>("Score");
	m_pScore->Init();
	m_pScore->AddComponent(std::make_shared<TextComponent>("Score: 0", font));
	m_pScore->AddComponent(std::make_shared<RenderComponent>(m_pScore->GetComponent<TextComponent>()->GetTextureComponent()));
	m_pScore->SetPosition(220, 60);
	AddGameObject(m_pScore);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pFPSText = std::make_shared<GameObject>("FPSText");
	m_pFPSText->Init();
	m_pFPSText->AddComponent(std::make_shared<TextComponent>("FPS:", font));
	m_pFPSText->AddComponent(std::make_shared<RenderComponent>(m_pFPSText->GetComponent<TextComponent>()->GetTextureComponent()));
	m_pFPSText->SetPosition(550, 10);
	AddGameObject(m_pFPSText);

	m_pFPS = std::make_shared<GameObject>("FPS");
	m_pFPS->Init();
	m_pFPS->AddComponent(std::make_shared<TextComponent>(std::to_string(time.GetFps()), font));
	m_pFPS->AddComponent(std::make_shared<FPSComponent>(m_pFPS->GetComponent<TextComponent>()));
	m_pFPS->AddComponent(std::make_shared<RenderComponent>(m_pFPS->GetComponent<TextComponent>()->GetTextureComponent()));
	m_pFPS->SetPosition(590, 10);
	AddGameObject(m_pFPS);
}

void dae::LevelScene::Update()
{
	Scene::Update();
	m_pTheGrid->Update();
	m_pTheGrid->CheckForCollision();
	m_pScore->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(Score::m_Score));
}

void dae::LevelScene::Render() const
{
	Scene::Render();
	m_pTheGrid->Draw();
}

void dae::LevelScene::InitPlayer1Controles(std::shared_ptr<Character> gameObject)
{
	auto& input = InputManager::GetInstance();
	std::string name = "P1LeftRun";
	const InputAction LeftRun = { name,InputTriggerState::Down,SDL_SCANCODE_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT };
	input.MapInput(LeftRun, std::make_shared<RunLeftCommand>(gameObject, shared_from_this()));
	name = "P1RightRun";
	const InputAction RightRun = { name,InputTriggerState::Down,SDL_SCANCODE_RIGHT,-1,XINPUT_GAMEPAD_DPAD_RIGHT };
	input.MapInput(RightRun, std::make_shared<RunRightCommand>(gameObject, shared_from_this()));
	name = "P1UpRun";
	const InputAction UpRun = { name,InputTriggerState::Down,SDL_SCANCODE_UP,-1,XINPUT_GAMEPAD_DPAD_UP };
	input.MapInput(UpRun, std::make_shared<RunUpCommand>(gameObject, shared_from_this()));
	name = "P1DownRun";
	const InputAction DownRun = { name,InputTriggerState::Down,SDL_SCANCODE_DOWN,-1,XINPUT_GAMEPAD_DPAD_DOWN };
	input.MapInput(DownRun, std::make_shared<RunDownCommand>(gameObject, shared_from_this()));

	name = "P1Action";
	const InputAction Push = { name,InputTriggerState::Pressed,SDL_SCANCODE_SPACE,-1,XINPUT_GAMEPAD_A };
	input.MapInput(Push, std::make_shared<ActionCommand>(gameObject, shared_from_this()));

	name = "P1Restart";
	InputAction Restart = { name,InputTriggerState::Pressed,SDL_SCANCODE_R,-1,XINPUT_GAMEPAD_BACK };
	input.MapInput(Restart, std::make_shared<ResetCommand>(gameObject, shared_from_this()));

	name = "P1Exit";
	const InputAction Exit = { name,InputTriggerState::Pressed,SDL_SCANCODE_ESCAPE,-1,XINPUT_GAMEPAD_START };
	input.MapInput(Exit, std::make_shared<ExitCommand>(gameObject, shared_from_this()));
}

void dae::LevelScene::InitPlayer2Controles(std::shared_ptr<Character> gameObject)
{
	auto& input = InputManager::GetInstance();
	input.SetNrOfPlayers(2);
	std::string name = "P2LeftRun";
	const InputAction LeftRun = { name,InputTriggerState::Down,SDL_SCANCODE_LEFT,-1,XINPUT_GAMEPAD_DPAD_LEFT,GamepadIndex::PlayerTwo };
	input.MapInput(LeftRun, std::make_shared<RunLeftCommand>(gameObject, shared_from_this()));
	name = "P2RightRun";
	const InputAction RightRun = { name,InputTriggerState::Down,SDL_SCANCODE_RIGHT,-1,XINPUT_GAMEPAD_DPAD_RIGHT,GamepadIndex::PlayerTwo };
	input.MapInput(RightRun, std::make_shared<RunRightCommand>(gameObject, shared_from_this()));
	name = "P2UpRun";
	const InputAction UpRun = { name,InputTriggerState::Down,SDL_SCANCODE_UP,-1,XINPUT_GAMEPAD_DPAD_UP,GamepadIndex::PlayerTwo };
	input.MapInput(UpRun, std::make_shared<RunUpCommand>(gameObject, shared_from_this()));
	name = "P2DownRun";
	const InputAction DownRun = { name,InputTriggerState::Down,SDL_SCANCODE_DOWN,-1,XINPUT_GAMEPAD_DPAD_DOWN,GamepadIndex::PlayerTwo };
	input.MapInput(DownRun, std::make_shared<RunDownCommand>(gameObject, shared_from_this()));

	name = "P2Action";
	const InputAction Push = { name,InputTriggerState::Pressed,SDL_SCANCODE_SPACE,-1,XINPUT_GAMEPAD_A ,GamepadIndex::PlayerTwo };
	input.MapInput(Push, std::make_shared<ActionCommand>(gameObject, shared_from_this()));

	name = "P2Restart";
	InputAction Restart = { name,InputTriggerState::Pressed,SDL_SCANCODE_R,-1,XINPUT_GAMEPAD_BACK ,GamepadIndex::PlayerTwo };
	input.MapInput(Restart, std::make_shared<ResetCommand>(gameObject, shared_from_this()));

	name = "P2Exit";
	const InputAction Exit = { name,InputTriggerState::Pressed,SDL_SCANCODE_ESCAPE,-1,XINPUT_GAMEPAD_START,GamepadIndex::PlayerTwo };
	input.MapInput(Exit, std::make_shared<ExitCommand>(gameObject, shared_from_this()));
}

void dae::LevelScene::Reset()const
{
	m_pTheGrid->Reset();
}

void dae::LevelScene::Restart()
{
	auto& scene = SceneManager::GetInstance();
	scene.SetActiveScene("Menu");
	RemoveGameObject(m_pFPS);
	RemoveGameObject(m_pFPSText);
	RemoveGameObject(m_pScore);
	RemoveGameObject(m_pTitle);
	m_pTheGrid->Restart();
}

dae::LevelScene::LevelScene(const std::string& name, const std::string& LevelFile) :Scene(name), m_FilePath(LevelFile)
{
}

dae::LevelScene::~LevelScene() = default;