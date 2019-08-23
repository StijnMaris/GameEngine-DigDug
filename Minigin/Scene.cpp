#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::AddGameObject(const std::shared_ptr<GameObject> gameObject)
{
	m_pGameObjects.push_back(gameObject);
}

void dae::Scene::RemoveGameObject(const std::shared_ptr<GameObject> gameObject)
{
	m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), gameObject), m_pGameObjects.end());
}

void dae::Scene::Update()
{
	for (auto gameObject : m_pGameObjects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_pGameObjects)
	{
		gameObject->Render();
	}
}