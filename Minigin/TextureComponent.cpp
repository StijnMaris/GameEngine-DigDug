#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::TextureComponent::TextureComponent(const std::string& filename) :BaseComponent("TextureComponent")
{
	SetTexture(filename);
}

dae::TextureComponent::TextureComponent(const std::shared_ptr<TextComponent> textComponent) :
	BaseComponent("TextureComponent")
{
	m_pTextComponent = textComponent;
}

void dae::TextureComponent::Update()
{
	if (m_pTextComponent)
	{
		m_pTexture = m_pTextComponent.get()->GetTextTexture();
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()const
{
	return m_pTexture;
}