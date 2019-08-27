#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Time.h"

dae::SpriteComponent::SpriteComponent(std::shared_ptr<TextureComponent> textureComp, int rows, int cols, int startRow, bool isAnimated, int speed) :
	BaseComponent("SpriteComponent"),
	m_pTextureComp(textureComp), m_Rows(rows), m_Cols(cols), m_IsAnimated(isAnimated), m_AnimSpeed(speed), m_StartRow(startRow)
{
	SetOffset(glm::vec2(0.5f));

	SDL_QueryTexture(textureComp->GetTexture()->GetSDLTexture(), nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
	if (m_Rows > 0 && m_Cols > 0)
	{
		m_SpriteWidth = m_TextureWidth / m_Cols;
		m_SpriteHeight = m_TextureHeight / m_Rows;
	}
	m_RectToDraw.x = 0;
	m_RectToDraw.y = m_StartRow * m_SpriteHeight;
	m_RectToDraw.w = static_cast<int>(m_SpriteWidth);
	m_RectToDraw.h = static_cast<int>(m_SpriteHeight);
}

void dae::SpriteComponent::Update()
{
	if (m_IsAnimated)
	{
		m_RectToDraw.x = m_SpriteWidth * (static_cast<int>(SDL_GetTicks() / m_AnimSpeed) % m_Cols);
	}
}