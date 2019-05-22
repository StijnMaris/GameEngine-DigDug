#include "MiniginPCH.h"
#include "GameObject.h"
#include <memory>
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

dae::GameObject::GameObject(const std::string& name) :m_Name(name)
{
}

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
	component->SetOwner(shared_from_this());
}

template <class T>
std::shared_ptr<T>  dae::GameObject::GetComponent() const
{
	for (auto component : m_pComponents)
	{
		/*std::shared_ptr<BaseComponent> comp = component.lock();
		if (comp)
		{*/
		auto test = std::dynamic_pointer_cast<T>(component);
		if (test && typeid(*component) == typeid(T))
		{
			return test;
		}
		/*}*/
	}
	return nullptr;
}

void dae::GameObject::Init()
{
	AddComponent(std::make_shared<Transform>());
}

void dae::GameObject::Update()
{
	for (auto component : m_pComponents)
	{
		/*std::shared_ptr<BaseComponent> comp = component.lock();
		if (comp)
		{
			comp->Update();
		}*/

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
		/*std::shared_ptr<BaseComponent> comp = component.lock();
		if (comp)
		{
			auto Rendr = std::dynamic_pointer_cast<RenderComponent>(comp);
			if (Rendr)
			{
				return true;
			}
		}*/

		auto Rendr = std::dynamic_pointer_cast<RenderComponent>(component);
		if (Rendr)
		{
			return true;
		}
	}
	return false;
}