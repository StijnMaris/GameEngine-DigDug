#pragma once
#include <glm/vec3.hpp>

namespace dae {
	enum class ButtonState
	{
		Idle = 0,
		Highlighted = 1,
		Pressed = 2
	};
	class GameObject;
	class MenuButton
	{
	public:
		MenuButton(std::string& name, std::string& file, std::string& levelName);
		~MenuButton();

		void Init();
		void Update();

		std::shared_ptr<GameObject> GetButton() const
		{
			return m_pButton;
		}

		ButtonState GetButtonState() const
		{
			return m_ButtonState;
		}

		void SetButtonState(ButtonState newState)
		{
			m_ButtonState = newState;
		}

		std::string GetLevelPath() const
		{
			return m_LevelPathName;
		}

	private:
		std::shared_ptr<GameObject> m_pButton;
		ButtonState m_ButtonState;

		std::string m_PathName;

		std::string m_LevelPathName;
	};
}
