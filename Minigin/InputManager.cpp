#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

dae::InputManager::InputManager()
{
	m_pButtons.insert_or_assign(ControllerButton::DpadRight, std::make_shared<RunRightCommand>());
	m_pButtons.insert_or_assign(ControllerButton::DpadUp, std::make_shared<RunUpCommand>());
	m_pButtons.insert_or_assign(ControllerButton::DpadLeft, std::make_shared<RunLeftCommand>());
	m_pButtons.insert_or_assign(ControllerButton::DpadDown, std::make_shared<RunDownCommand>());
	//m_pButtons.insert_or_assign(ControllerButton::L1, std::make_shared<ExitCommand>());
	m_pButtons.insert_or_assign(ControllerButton::Exit, std::make_shared<ExitCommand>());
}

bool dae::InputManager::HandleInput()
{
	bool cont{};
	for (std::pair<ControllerButton, std::shared_ptr<Command>> element : m_pButtons)
	{
		if (!IsPressed(element.first)) {
			cont = true;
		}
		else {
			cont = element.second->execute();
			if (cont)
			{
			}
			else
			{
				return false;
			}
		}
	}

	RtlSecureZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);
	return cont;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return currentState.Gamepad.wButtons & static_cast<int>(button);
}

void dae::InputManager::MapInput(ControllerButton button, std::shared_ptr<Command> command)
{
	m_pButtons.at(button) = command;
}