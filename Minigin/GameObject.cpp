#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
//#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

dae::GameObject::GameObject(const std::string& name) :m_Name(name)
{
}

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_pComponents.push_back(component);
}

template <class T>
std::shared_ptr<std::is_base_of<dae::BaseComponent, T>>& dae::GameObject::GetComponent()
{
	for (auto component : m_pComponents)
	{
		if (dynamic_cast<T>(component))
		{
			return component;
		}
	}
	return nullptr;
}

void dae::GameObject::Update()
{
	for (auto component : m_pComponents)
	{
		//component->Update();
	}
}

void dae::GameObject::Render() const
{
	const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}