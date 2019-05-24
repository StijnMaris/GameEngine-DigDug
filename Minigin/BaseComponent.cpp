#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::string name) :m_Name(name)
{
}

std::shared_ptr<dae::GameObject> dae::BaseComponent::GetOwner() const
{
	std::shared_ptr<GameObject> owner = m_pOwner.lock();
	if (owner)
		return  owner;
	std::cout << "owner not found" << std::endl;
	return nullptr;
}

void dae::BaseComponent::SetOwner(std::shared_ptr<GameObject> owner)
{
	m_pOwner = owner;
}