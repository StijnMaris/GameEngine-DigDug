#include "MiniginPCH.h"
#include "GameObject.h"
#include <memory>
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "BaseComponent.h"
#include "CommandComponent.h"

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
	if (HasRenderComponent())
	{
		GetComponent<RenderComponent>()->Render();
	}
	auto rend3 = GetComponent<TextureComponent>();
	auto rend4 = GetComponent<TextComponent>();
	auto rend5 = GetComponent<CommandComponent>();
	auto rend6 = GetComponent<SpriteComponent>();
	auto pos = GetComponent<Transform>();
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return  GetComponent<Transform>()->GetPosition();
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	GetComponent<Transform>()->SetPosition(x, y, z);
}

void dae::GameObject::SetPosition(glm::vec3 pos)
{
	GetComponent<Transform>()->SetPosition(pos);
}

const glm::vec3& dae::GameObject::GetScale() const
{
	return  GetComponent<Transform>()->GetScale();
}

void dae::GameObject::SetScale(float x, float y, float z)
{
	GetComponent<Transform>()->SetScale(x, y, z);
}

void dae::GameObject::SetScale(glm::vec3 scale)
{
	GetComponent<Transform>()->SetScale(scale);
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