#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(std::shared_ptr<TextureComponent> textureComponent) :
	BaseComponent("RenderComponent"), m_pTextureComponent(textureComponent)
{
	m_IsSprite = false;
}

dae::RenderComponent::RenderComponent(std::shared_ptr<SpriteComponent> sprite) : BaseComponent("RenderComponent"), m_pTextureComponent(sprite->GetTextureComp()), m_pSpriteComponent(sprite)
{
	m_IsSprite = true;
}

void dae::RenderComponent::Render()const
{
	if (!m_IsSprite)
	{
		Renderer::GetInstance().RenderTexture(*m_pTextureComponent->GetTexture(), GetOwner()->GetPosition().x, GetOwner()->GetPosition().y);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_pTextureComponent->GetTexture(), m_pSpriteComponent);
	}
}