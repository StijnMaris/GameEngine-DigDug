#include "MiniginPCH.h"
#include "MenuScene.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "InputManager.h"

dae::MenuScene::MenuScene(const std::string& name) :Scene(name)
{
	m_BackGroundPos = { 224,288 };
	m_ButtonPos = { 75,550 };
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

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("Single Player");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("PRESS 1 FOR SINGLE PLAYER", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(m_ButtonPos.x, m_ButtonPos.y);
	AddGameObject(to);

	to = std::make_shared<GameObject>("Two Player");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("PRESS 2 FOR TWO PLAYERS", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(m_ButtonPos.x, m_ButtonPos.y + m_ButtonPos.x);
	AddGameObject(to);

	to = std::make_shared<GameObject>("VS Player");
	to->Init();
	to->AddComponent(std::make_shared<TextComponent>("PRESS 3 FOR VS PLAYER", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(m_ButtonPos.x, m_ButtonPos.y + m_ButtonPos.x * 2);
	AddGameObject(to);
}

void dae::MenuScene::Update()
{
	Scene::Update();
}

void dae::MenuScene::Render() const
{
	Scene::Render();
}

void dae::MenuScene::InitMenuControls()
{
	/*auto& input = InputManager::GetInstance();
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
	input.MapInput(Exit, std::make_shared<ExitCommand>(gameObject, shared_from_this()));*/
}