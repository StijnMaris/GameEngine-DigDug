#include "MiniginPCH.h"
#include "GameObject.h"
#include <memory>
#include "RenderComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "BaseComponent.h"
#include "CommandComponent.h"
#include "ColliderComponent.h"
#include "MovementComponent.h"
#include "ActionComponent.h"
#include "ButtonComponent.h"

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
		/*if (m_pComponents.size() == 8)
		{
			component->Update();
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

	//if i dont do this i get linker errors up the wazzu
	auto rend3 = GetComponent<TextureComponent>();
	auto rend4 = GetComponent<TextComponent>();
	auto rend5 = GetComponent<CommandComponent>();
	auto rend7 = GetComponent<ColliderComponent>();
	auto rend6 = GetComponent<SpriteComponent>();
	auto rend8 = GetComponent<MovementComponent>();
	auto rend9 = GetComponent<ActionComponent>();
	auto rend10 = GetComponent<ButtonComponent>();
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
		auto Rendr = std::dynamic_pointer_cast<RenderComponent>(component);
		if (Rendr)
		{
			return true;
		}
	}
	return false;
}