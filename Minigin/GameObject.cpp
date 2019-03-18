#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "RenderComponent.h"
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
T dae::GameObject::GetComponent() const
{
	for (auto component : m_pComponents)
	{
		auto test = std::dynamic_pointer_cast<T>(component);
		if (test)
		{
			return *test;
		}
	}
	return RenderComponent{};
}

void dae::GameObject::Update()
{
	for (auto component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	const auto pos = mTransform.GetPosition();
	if (HasRenderComponent())
	{
		auto rendr = GetComponent<RenderComponent>();
		rendr.Render(pos.x, pos.y);
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}

bool dae::GameObject::HasRenderComponent()const
{
	for (auto component : m_pComponents)
	{
		auto test = std::dynamic_pointer_cast<RenderComponent>(component);
		if (test)
		{
			return true;
		}
	}
	return false;
}