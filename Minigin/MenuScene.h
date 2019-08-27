#pragma once
#include "Scene.h"
#include <glm/vec2.hpp>

namespace dae {
	class MenuButton;
	class MenuScene final : public Scene
	{
	public:
		MenuScene(const std::string& name);
		~MenuScene() = default;

		void Init();

		void Update() override;
		void Render() const override;

		void InitMenuControls();

		std::vector<std::shared_ptr<MenuButton>>GetMenu()
		{
			return m_pButtons;
		}

	private:
		glm::vec2 m_BackGroundPos;

		glm::vec2 m_ButtonPos;

		bool m_NeedsUpdate;

		std::vector<std::shared_ptr<MenuButton>> m_pButtons;
		std::vector<std::string> m_Names;
	};
}
