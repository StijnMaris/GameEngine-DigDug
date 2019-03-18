#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename) :BaseComponent("TextureComponent")
{
	SetTexture(filename);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()
{
	return m_Texture;
}