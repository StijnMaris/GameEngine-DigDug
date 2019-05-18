#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		860,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
	InputManager::GetInstance().Init();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& time = Time::GetInstance();

	auto go = std::make_shared<GameObject>("BackGround");
	go->AddComponent(std::make_shared<TextureComponent>("background.jpg"));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<TextureComponent>()));
	go->SetPosition(0, 0);
	scene.AddGameObject(go);

	go = std::make_shared<GameObject>("DAELogo");
	go->AddComponent(std::make_shared<TextureComponent>("logo.png"));
	go->AddComponent(std::make_shared<RenderComponent>(go->GetComponent<TextureComponent>()));
	go->SetPosition(216, 180);
	scene.AddGameObject(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("TitleText");
	to->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(80, 20);
	scene.AddGameObject(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	to = std::make_shared<GameObject>("FPSText");
	to->AddComponent(std::make_shared<TextComponent>("FPS:", font));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(570, 10);
	scene.AddGameObject(to);

	to = std::make_shared<GameObject>("FPS");
	to->AddComponent(std::make_shared<TextComponent>(std::to_string(time.GetFps()), font));
	to->AddComponent(std::make_shared<FPSComponent>(to->GetComponent<TextComponent>()));
	to->AddComponent(std::make_shared<RenderComponent>(to->GetComponent<TextComponent>()->GetTextureComponent()));
	to->SetPosition(610, 10);
	scene.AddGameObject(to);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& time = Time::GetInstance();

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			time.Update();

			//doContinue;
			input.HandleInput();

			sceneManager.Update();
			renderer.Render();
		}
	}
	std::cin.get();
	Cleanup();
}