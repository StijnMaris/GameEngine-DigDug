#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"

dae::SpriteComponent::SpriteComponent(std::shared_ptr<TextureComponent> textureComp, glm::vec2 size) : BaseComponent("SpriteComponent"), m_pTextureComp(textureComp)
{
	SetOffset(glm::vec2(0.5f));

	//SetRectToDraw();
	int TextureWidth = 0;
	int TextureHeight = 0;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &TextureWidth, &TextureHeight);

	m_RectToDraw.x = 0;
	m_RectToDraw.y = 0;
	m_RectToDraw.w = static_cast<int>(size.x);
	m_RectToDraw.h = static_cast<int>(size.y);
}

dae::SpriteComponent::~SpriteComponent()
{
}

void dae::SpriteComponent::Update()
{
}