#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::string name) :m_Name(name), m_pOwner(nullptr)
{
}

std::shared_ptr<dae::GameObject> dae::BaseComponent::GetOwner() const
{
	return  m_pOwner;
}

void dae::BaseComponent::SetOwner(std::shared_ptr<GameObject> owner)
{
	m_pOwner = owner;
}