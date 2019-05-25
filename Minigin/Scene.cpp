#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
{
	m_pGameObjects.push_back(gameObject);
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