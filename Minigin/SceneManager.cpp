#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for (auto scene : m_pActiveScenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : m_pActiveScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	std::string current{};
	for (const auto scene : m_pActiveScenes)
	{
		current = scene->GetSceneName();
		if (scene->GetSceneName() == name)
		{
			return;
		}
	}

	for (const auto scene : m_pScenes)
	{
		if (scene->GetSceneName() == name)
		{
			DisableScene(current);
			m_pActiveScenes.push_back(scene);
			return;
		}
	}
}

void dae::SceneManager::DisableScene(const std::string& name)
{
	for (int i = 0; i < (int)m_pActiveScenes.size(); i++)
	{
		if (m_pActiveScenes[i]->GetSceneName() == name)
		{
			m_pActiveScenes.erase(m_pActiveScenes.begin() + i);
			--i;
			return;
		}
	}
}

bool dae::SceneManager::IsSceneActive(const std::string& name)
{
	for (const auto scene : m_pActiveScenes)
	{
		if (scene->GetSceneName() == name)
		{
			return true;
		}
	}
	return false;
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	return scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(std::shared_ptr<Scene> scene)
{
	m_pScenes.push_back(scene);
	return scene;
}

//dae::Scene& dae::SceneManager::GetScene(const std::string& name)
//{
//	for (const auto scene : m_pScenes)
//	{
//		if (scene->GetSceneName() == name)
//		{
//			return *scene;
//		}
//	}
//	return *m_pScenes[0];
//}