#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent() :BaseComponent("RenderComponent")
{
}

void dae::RenderComponent::Render(float posX, float posY)const
{
	Renderer::GetInstance().RenderTexture(*m_Texture.get()->GetTexture(), posX, posY);
}