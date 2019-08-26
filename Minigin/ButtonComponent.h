#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace dae {
	class TextComponent;
	class SpriteComponent;
	class ButtonComponent final : public BaseComponent
	{
	public:
		ButtonComponent(glm::vec2 pos, float width, float height, std::shared_ptr<TextComponent> textComponent,
			std::shared_ptr<SpriteComponent> spriteComponent,
			glm::vec3 normalColor = { 0.f,0.f,0.f },
			glm::vec3 highlightColor = { 255.f,255.f,0.f },
			glm::vec3 pressedColor = { 155.f,155.f,55.f });
		~ButtonComponent() = default;

		void Update() override;

		void OnClick();

		void SetText(std::string text)const;
		void SetSprite(std::string text)const;
	private:
		bool m_NeedsUpdate;

		glm::vec2 m_Pos;
		float m_Width;
		float m_Height;

		std::shared_ptr<TextComponent> m_pTextComponent;
		std::shared_ptr<SpriteComponent> m_pSpriteComponent;
		glm::vec3 m_NormalColor;
		glm::vec3 m_HighlightColor;
		glm::vec3 m_PressedColor;
	};
}
