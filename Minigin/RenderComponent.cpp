#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(std::shared_ptr<TextureComponent> textureComponent) :BaseComponent("RenderComponent")
{
	m_pTextureComponent = textureComponent;
}

void dae::RenderComponent::Render(float posX, float posY)const
{
	Renderer::GetInstance().RenderTexture(*m_pTextureComponent.get()->GetTexture(), posX, posY);
}