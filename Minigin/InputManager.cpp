#include "MiniginPCH.h"
#include "InputManager.h"
#include <minwinbase.h>
#include <iostream>
#include "GameObject.h"

//*******************//
//***INPUTMANAGER***//
//*******************//
dae::InputManager::InputManager()
{
}

dae::InputManager::~InputManager()
{
	KBcurrentState.clear();
	KBpreviousState.clear();
	m_pButtons.clear();
}

void dae::InputManager::Init()
{
	if (m_IsInitialized)
		throw std::exception("InputManager::Init() > The inputmanager has already been initalized");
	//Init keyboard and mouse

	m_UseKeyboard = true;

	KBcurrentState.insert(KBcurrentState.begin(), 256, false);
	KBpreviousState.insert(KBpreviousState.begin(), 256, false);

	if (InitGamepads())
		m_UseGamepad = true;

	std::cout << "Finished initalizing the input manager" << std::endl;
	std::cout << "Number of connected gamepads: " << nGamepads << std::endl;

	m_IsInitialized = true;
}

void dae::InputManager::MapInput(InputAction button, std::shared_ptr<Command> command)
{
	auto it = m_pButtons.find(button.ActionID);
	if (it != m_pButtons.end())
		m_pButtons.at(button.ActionID) = std::make_pair(button, command);

	m_pButtons[button.ActionID] = std::make_pair(button, command);
}

bool dae::InputManager::InitGamepads()
{
	int playerID = -1;
	XINPUT_STATE state;
	for (DWORD i = 0; i < XUSER_MAX_COUNT && playerID == -1; i++)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			playerID = i;
	}

	if (playerID != -1)
	{
		m_pGamePads.push_back(std::make_shared<Gamepad>(playerID));
	}
	//Set number of gamepads
	nGamepads = (unsigned int)m_pGamePads.size();
	//Does every player have a gamepad?
	if (nGamepads != nPlayers)
		return false;

	// select current player
	currentlyActivePlayer = 0;
	if (m_pGamePads.size() > 0)
		m_pCurrentGamePad = m_pGamePads[0];

	return true;
}

void dae::InputManager::ProcessInput()
{
	if (m_UseKeyboard)
		ProcessKeyboardInput();
	if (m_UseGamepad)
		ProcessGamePadInput();
	HandleInput();
}

void dae::InputManager::RefreshInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousState, sizeof(XINPUT_STATE));
}

bool dae::InputManager::IsActionTriggered(int actionID)
{
	return m_pButtons.at(actionID).first.IsTriggered;
}

const dae::InputTriggerState dae::InputManager::GetKeystrokeState(int key) const
{
	InputTriggerState outKS = InputTriggerState::Idle;
	if (IsKeyPressed(key, true))
	{
		if (IsKeyPressed(key))
			outKS = InputTriggerState::Down;
		else
			outKS = InputTriggerState::Released;
	}
	else
	{
		if (IsKeyPressed(key))
			outKS = InputTriggerState::Pressed;
		else
			outKS = InputTriggerState::Idle;
	}
	return outKS;
}

void dae::InputManager::HandleInput()
{
	//Loop for every inputaction that is mapped
	for (auto it = m_pButtons.begin(); it != m_pButtons.end(); ++it)
	{
		auto currAction = &(it->second.first);
		currAction->IsTriggered = false;

		//GAMEPAD
		if (m_UseGamepad && currAction->GamepadButtonCode != 0)
		{
			if (m_pGamePads[static_cast<int>(currAction->PlayerIndex)])
			{
				auto ks = m_pGamePads[static_cast<int>(currAction->PlayerIndex)]->GetButtonState(currAction->GamepadButtonCode);
				if (ks == currAction->TriggerState)
					currAction->IsTriggered = true;
			}
		}
		//KEYBOARD
		if (!currAction->IsTriggered && m_UseKeyboard && currAction->KeyboardCode != -1)
		{
			auto ks = GetKeystrokeState(currAction->KeyboardCode);
			if (ks == currAction->TriggerState)
				currAction->IsTriggered = true;
		}

		if (currAction->IsTriggered)
		{
			if (currAction->ActionID == 16)
				it->second.second->execute();
			it->second.second->AddToCommandStream();
			//std::cout << it->second.first.PlayerIndex << std::endl;
		}
	}
}

//*******************//
//*****KEYBOARD*****//
//*******************//

//Setting the current and previous states for the Keyboard
void dae::InputManager::ProcessKeyboardInput()
{
	KBpreviousState = KBcurrentState;
	for (unsigned int i = 0; i < KBcurrentState.size(); ++i)
		KBcurrentState[i] = GetAsyncKeyState(i);
}

bool dae::InputManager::IsKeyPressed(int key, bool prevFrame) const
{
	if (!prevFrame)
		return  (KBcurrentState[key] != 0);
	else
		return  (KBpreviousState[key] != 0);
}

const glm::vec2 dae::InputManager::getLStick() const
{
	return m_pCurrentGamePad->m_ThumbStickL;
}

const glm::vec2 dae::InputManager::getRStick() const
{
	return m_pCurrentGamePad->m_ThumbStickR;
}

bool dae::InputManager::IsGamepadConnected(GamepadIndex index) const
{
	if (m_pGamePads[(DWORD)index] == nullptr)
	{
		return false;
	}
	return true;
}

//*******************//
//******GAMEPAD******//
//*******************//

dae::Gamepad::Gamepad(const unsigned playerId)
	: playerID(playerId)
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousState, sizeof(XINPUT_STATE));

	//Thumbsticks
	m_ThumbStickL = glm::vec2(0, 0);
	m_ThumbStickR = glm::vec2(0, 0);
}

//Setting the current and previous states for the gamepads
void dae::InputManager::ProcessGamePadInput()
{
	for (auto& gamepad : m_pGamePads)
	{
		gamepad->GetState();
	}
}

//Keystates
const dae::InputTriggerState dae::Gamepad::GetButtonState(WORD button) const
{
	InputTriggerState outKS = InputTriggerState::Idle;
	if (WasPressed(button))
	{
		if (IsPressed(button))
			outKS = InputTriggerState::Down;
		else
			outKS = InputTriggerState::Released;
	}
	else
	{
		if (IsPressed(button))
			outKS = InputTriggerState::Pressed;
		else
			outKS = InputTriggerState::Idle;
	}
	return outKS;
}

//Double buffer the input
bool dae::Gamepad::WasPressed(WORD button) const
{
	return (previousState.Gamepad.wButtons& button) != 0;
}

bool dae::Gamepad::IsPressed(WORD button) const
{
	return (currentState.Gamepad.wButtons& button) != 0;
}

bool dae::Gamepad::checkConnection()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	return(XInputGetState(playerID, &state) == ERROR_SUCCESS);
}

void dae::Gamepad::GetState()
{
	//Check if still connected
	if (!checkConnection())
		throw std::exception("Gamepad::GetState() > Controller was disconnected");

	// save state
	CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));

	// get current state
	if (XInputGetState(playerID, &currentState) != ERROR_SUCCESS)
		throw std::exception("Gamepad::GetState() > Unable to poll gamepad!");

	// check if something changed
	if (previousState.dwPacketNumber == currentState.dwPacketNumber)
		return;

	// get axes
	m_ThumbStickL.x = static_cast<float>(currentState.Gamepad.sThumbLX);
	m_ThumbStickL.y = static_cast<float>(currentState.Gamepad.sThumbLY);
	m_ThumbStickR.x = static_cast<float>(currentState.Gamepad.sThumbRX);
	m_ThumbStickR.y = static_cast<float>(currentState.Gamepad.sThumbRY);

	GetFixedThumbStick(m_ThumbStickL, true);
	GetFixedThumbStick(m_ThumbStickR, false);
}

void dae::Gamepad::GetFixedThumbStick(glm::vec2& thumbStick, bool isLeft)
{
	float magnitude = sqrt(thumbStick.x*thumbStick.x + thumbStick.y*thumbStick.y);
	//determine the direction the controller is pushed
	float normalizedLX = thumbStick.x / magnitude;
	float normalizedLY = thumbStick.y / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > (isLeft ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= (isLeft ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - (isLeft ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}
	thumbStick.x = normalizedLX * normalizedMagnitude;
	thumbStick.y = normalizedLY * normalizedMagnitude;
}