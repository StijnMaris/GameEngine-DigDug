#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace dae {
	class ButtonComponent final : public BaseComponent
	{
	public:
		ButtonComponent(glm::vec3 normalColor = { 0.f,0.f,0.f },
			glm::vec3 highlightColor = { 255.f,255.f,0.f },
			glm::vec3 pressedColor = { 155.f,155.f,55.f });
		~ButtonComponent() = default;

		void Update() override;

		void OnClick(std::string levelName);

	private:
		glm::vec3 m_NormalColor;
		glm::vec3 m_HighlightColor;
		glm::vec3 m_PressedColor;
	};
}
