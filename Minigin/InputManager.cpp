#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>

using namespace dae;

PBYTE InputManager::m_pCurrKeyboardState = nullptr;
PBYTE InputManager::m_pOldKeyboardState = nullptr;
PBYTE InputManager::m_pKeyboardState0 = nullptr;
PBYTE InputManager::m_pKeyboardState1 = nullptr;
bool InputManager::m_KeyboardState0Active = true;
POINT InputManager::m_OldMousePosition = POINT();
POINT InputManager::m_CurrMousePosition = POINT();
POINT InputManager::m_MouseMovement = POINT();
XINPUT_STATE InputManager::m_OldGamepadState[XUSER_MAX_COUNT];
XINPUT_STATE InputManager::m_CurrGamepadState[XUSER_MAX_COUNT];
bool InputManager::m_ConnectedGamepads[XUSER_MAX_COUNT];
bool InputManager::m_Enabled = true;
bool InputManager::m_IsInitialized = false;

dae::InputManager::InputManager()
{
	m_pButtons.insert_or_assign(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_shared<RunRightCommand>());
	m_pButtons.insert_or_assign(VK_UP, std::make_shared<RunUpCommand>());
	m_pButtons.insert_or_assign(XINPUT_GAMEPAD_DPAD_LEFT, std::make_shared<RunLeftCommand>());
	m_pButtons.insert_or_assign(XINPUT_GAMEPAD_DPAD_UP, std::make_shared<RunDownCommand>());
	//m_pButtons.insert_or_assign(ControllerButton::L1, std::make_shared<ExitCommand>());
	m_pButtons.insert_or_assign(XINPUT_GAMEPAD_START, std::make_shared<ExitCommand>());
}

void  dae::InputManager::HandleInput()
{
	for (std::pair<int, std::pair<InputAction, std::shared_ptr<Command>>> element : m_pButtons)
	{
		if (!IsPressed(element.second.first)) {
		}
		else {
			element.second.second;
		}
	}

	RtlSecureZeroMemory(&m_CurrGamepadState, sizeof(XINPUT_STATE));
	XInputGetState(0, m_CurrGamepadState);
}

bool dae::InputManager::IsPressed(InputAction button) const
{
	return m_CurrGamepadState->Gamepad.wButtons & static_cast<InputAction>(button);
}

void dae::InputManager::MapInput(InputAction button, std::shared_ptr<Command> command)
{
	m_pButtons.at(button) = command;
}

bool InputManager::IsActionTriggered(int actionID)
{
	return m_pButtons.at(actionID).first.IsTriggered;
}

bool InputManager::IsKeyboardKeyDown(int key, bool previousFrame)
{
	if (!m_pCurrKeyboardState || !m_pOldKeyboardState)
		return false;

	if (key > 0x07 && key <= 0xFE)
		if (previousFrame)
			return (m_pOldKeyboardState[key] & 0xF0) != 0;

	return false;
}

bool InputManager::IsMouseButtonDown(int button, bool previousFrame)
{
}

bool InputManager::IsGamepadButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame)
{
}

glm::vec2 InputManager::GetThumbstickPosition(bool leftThumbstick, GamepadIndex playerIndex)
{
	glm::vec2 pos;
	if (leftThumbstick)
	{
		pos = glm::vec2(m_CurrGamepadState[playerIndex].Gamepad.sThumbLX, m_CurrGamepadState[playerIndex].Gamepad.sThumbLY);

		if (pos.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pos.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)pos.x = 0;
		if (pos.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pos.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)pos.y = 0;
	}
	else
	{
		pos = glm::vec2(m_CurrGamepadState[playerIndex].Gamepad.sThumbRX, m_CurrGamepadState[playerIndex].Gamepad.sThumbRY);

		if (pos.x > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pos.x < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)pos.x = 0;
		if (pos.y > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pos.y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)pos.y = 0;
	}

	if (pos.x < 0)pos.x /= 32768;
	else pos.x /= 32767;

	if (pos.y < 0)pos.y /= 32768;
	else pos.y /= 32767;

	return pos;
}

float InputManager::GetTriggerPressure(bool leftTrigger, GamepadIndex playerIndex)
{
	if (leftTrigger)
	{
		return m_CurrGamepadState[playerIndex].Gamepad.bLeftTrigger / 255.0f;
	}
	else
	{
		return m_CurrGamepadState[playerIndex].Gamepad.bRightTrigger / 255.0f;
	}
}

void InputManager::SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex)
{
	XINPUT_VIBRATION vibration;
	leftVibration = std::clamp(leftVibration, 0.0f, 1.0f);
	rightVibration = std::clamp(rightVibration, 0.0f, 1.0f);

	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = static_cast<WORD>(leftVibration * 65535);
	vibration.wRightMotorSpeed = static_cast<WORD>(rightVibration * 65535);

	XInputSetState(playerIndex, &vibration);
}

void InputManager::UpdateGamepadStates()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		m_OldGamepadState[i] = m_CurrGamepadState[i];

		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &m_CurrGamepadState[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

bool InputManager::UpdateKeyboardStates()
{
	BOOL getKeyboardResult;
	if (m_KeyboardState0Active)
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_KeyboardState0Active = !m_KeyboardState0Active;

	return getKeyboardResult > 0 ? true : false;
}

void dae::InputManager::RefreshControllerConnections()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}