#pragma once
#include "Scene.h"
#include <glm/vec2.hpp>

namespace dae {
	class MenuScene final : public Scene
	{
	public:
		MenuScene(const std::string& name);
		~MenuScene() = default;

		void Init();

		void Update() override;
		void Render() const override;

		void InitMenuControls();

	private:
		glm::vec2 m_BackGroundPos;

		glm::vec2 m_ButtonPos;
	};
}
