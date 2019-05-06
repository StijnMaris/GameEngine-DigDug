#pragma once
#include <XInput.h>
#include "Command.h"
#include <memory>
#include "Singleton.h"
#include <map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		DpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DpadUp = XINPUT_GAMEPAD_DPAD_UP,
		DpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		R1 = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		L1 = XINPUT_GAMEPAD_LEFT_SHOULDER,
		Exit = XINPUT_GAMEPAD_START
		//Analog = XINPUT_KEYSTROKE_KEYUP
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool HandleInput();
		bool IsPressed(ControllerButton button) const;

		void MapInput(ControllerButton button, std::shared_ptr<Command> command);

	private:
		XINPUT_STATE currentState{};
		std::map<ControllerButton, std::shared_ptr<Command> > m_pButtons;
	};
}
