#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Time.h"
#include "Scene.h"
#include "LevelScene.h"
#include "MenuScene.h"

bool dae::Minigin::m_DoContinue = true;

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
		608,
		796,
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
	auto&sceneMan = SceneManager::GetInstance();
	std::shared_ptr<Scene> level = sceneMan.CreateScene(std::make_shared<LevelScene>("Level1SP", "../Data/Level1SP.txt"));
	std::dynamic_pointer_cast<LevelScene>(level)->Init();
	level = sceneMan.CreateScene(std::make_shared<LevelScene>("Level1MP", "../Data/Level1MP.txt"));
	std::dynamic_pointer_cast<LevelScene>(level)->Init();
	level = sceneMan.CreateScene(std::make_shared<LevelScene>("Level1VSP", "../Data/Level1VSP.txt"));
	std::dynamic_pointer_cast<LevelScene>(level)->Init();
	//sceneMan.SetActiveScene("Level");

	const std::shared_ptr<Scene> menu = sceneMan.CreateScene(std::make_shared<MenuScene>("Menu"));
	std::dynamic_pointer_cast<MenuScene>(menu)->Init();
	sceneMan.SetActiveScene("Menu");
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

		while (m_DoContinue)
		{
			time.Update();

			//doContinue;
			input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
		}
	}
	Cleanup();
}