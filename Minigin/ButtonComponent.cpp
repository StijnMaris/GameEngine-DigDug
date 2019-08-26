#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "SpriteComponent.h"

dae::ButtonComponent::ButtonComponent(glm::vec2 pos, float width, float height,
	std::shared_ptr<TextComponent> textComponent,
	std::shared_ptr<SpriteComponent> spriteComponent,
	glm::vec3 normalColor,
	glm::vec3 highlightColor,
	glm::vec3 pressedColor) :BaseComponent("ButtonComponent"),
	m_NeedsUpdate(false),
	m_Pos(pos),
	m_Width(width),
	m_Height(height),
	m_pTextComponent(textComponent),
	m_pSpriteComponent(spriteComponent),
	m_NormalColor(normalColor),
	m_HighlightColor(highlightColor),
	m_PressedColor(pressedColor)

{
}

void dae::ButtonComponent::Update()
{
	if (m_NeedsUpdate)
	{
	}
}

void dae::ButtonComponent::OnClick()
{
}

void dae::ButtonComponent::SetText(std::string text)const
{
	m_pTextComponent->SetText(text);
}

void dae::ButtonComponent::SetSprite(std::string text) const
{
	//m_pSpriteComponent->SetTexture()
}