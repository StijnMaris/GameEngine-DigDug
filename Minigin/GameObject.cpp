#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

dae::GameObject::GameObject(const std::string& name) :m_Name(name)
{
	AddComponent(std::make_shared<Transform>());
}

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_pComponents.push_back(component);
}

template <class T>
std::shared_ptr<T>  dae::GameObject::GetComponent() const
{
	for (auto component : m_pComponents)
	{
		auto test = std::dynamic_pointer_cast<T>(component);
		if (test && typeid(*component) == typeid(T))
		{
			return test;
		}
	}
	return nullptr;
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
	const auto pos = GetComponent<Transform>()->GetPosition();
	if (HasRenderComponent())
	{
		auto rendr = GetComponent<RenderComponent>();
		rendr->Render(pos.x, pos.y);
	}
	auto rend3 = GetComponent<TextureComponent>();
	auto rend4 = GetComponent<TextComponent>();
}

void dae::GameObject::SetPosition(float x, float y)
{
	GetComponent<Transform>()->SetPosition(x, y, 0.0f);
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