#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

dae::InputManager::InputManager()
{
	m_pButtons.insert_or_assign(ControllerButton::ButtonX, std::make_shared<FartCommand>());
	m_pButtons.insert_or_assign(ControllerButton::DpadUp, std::make_shared<FireCommand>());
	m_pButtons.insert_or_assign(ControllerButton::R1, std::make_shared<JumpCommand>());
	m_pButtons.insert_or_assign(ControllerButton::DpadDown, std::make_shared<DuckCommand>());
	m_pButtons.insert_or_assign(ControllerButton::L1, std::make_shared<DuckCommand>());
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
				
			}else
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