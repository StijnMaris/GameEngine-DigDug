#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::TextureComponent::TextureComponent(const std::string& filename) :BaseComponent("TextureComponent")
{
	SetTexture(filename);
}

dae::TextureComponent::TextureComponent(SDL_Texture* texture) :
	BaseComponent("TextureComponent")
{
	SetTexture(texture);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(SDL_Texture* texture)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()const
{
	return m_pTexture;
}