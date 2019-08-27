#include "MiniginPCH.h"
#include "InputManager.h"
#include <minwinbase.h>
#include <iostream>
#include "GameObject.h"
#include "Minigin.h"

//*******************//
//***INPUTMANAGER***//
//*******************//
dae::InputManager::InputManager()
{
}

dae::InputManager::~InputManager()
{
	m_pButtons.clear();
}

void dae::InputManager::Init()
{
	if (m_IsInitialized)
		throw std::exception("InputManager::Init() > The inputmanager has already been initalized");
	//Init keyboard and mouse

	m_UseKeyboard = true;

	if (InitGamepads())
		m_UseGamepad = true;

	std::cout << "Finished initalizing the input manager" << std::endl;
	std::cout << "Number of connected gamepads: " << m_NrGamepads << std::endl;

	m_IsInitialized = true;
}

void dae::InputManager::MapInput(InputAction button, std::shared_ptr<Command> command)
{
	const auto hash = std::hash<std::string>{}(button.m_ActionID);
	const auto it = m_pButtons.find(static_cast<int>(hash));
	if (it != m_pButtons.end())
		m_pButtons.at(static_cast<int>(hash)) = std::make_pair(button, command);

	m_pButtons[static_cast<int>(hash)] = std::make_pair(button, command);
}

bool dae::InputManager::InitGamepads()
{
	int playerID = -1;
	XINPUT_STATE state;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
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
	m_NrGamepads = (unsigned int)m_pGamePads.size();
	//Does every player have a gamepad?
	if (m_NrGamepads != m_NrPlayers)
		return false;

	// select current player
	m_CurrentlyActivePlayer = 0;
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
	m_pButtons.clear();
}

bool dae::InputManager::IsActionTriggered(int actionID)
{
	return m_pButtons.at(actionID).first.m_IsTriggered;
}

void dae::InputManager::HandleInput()
{
	//Loop for every inputaction that is mapped
	for (auto it = m_pButtons.begin(); it != m_pButtons.end(); ++it)
	{
		auto currAction = &(it->second.first);
		currAction->m_IsTriggered = false;

		//GAMEPAD
		if (m_UseGamepad && currAction->m_GamepadButtonCode != 0 && currAction->m_PlayerIndex != GamepadIndex::Menu)
		{
			if (m_pGamePads[static_cast<int>(currAction->m_PlayerIndex)])
			{
				auto ks = m_pGamePads[static_cast<int>(currAction->m_PlayerIndex)]->GetButtonState(currAction->m_GamepadButtonCode);
				if (ks == currAction->m_RequiredTriggerState)
					currAction->m_IsTriggered = true;
			}
		}
		//KEYBOARD
		if (!currAction->m_IsTriggered && m_UseKeyboard && currAction->m_KeyboardCode != -1)
		{
			if (currAction->m_CurrentTriggerState == currAction->m_RequiredTriggerState)
				currAction->m_IsTriggered = true;
		}

		if (currAction->m_IsTriggered)
		{
			it->second.second->AddToCommandStream();
		}
	}
}

//*******************//
//*****KEYBOARD*****//
//*******************//

//Setting the current and previous states for the Keyboard
void dae::InputManager::ProcessKeyboardInput()
{
	SDL_Event e;
	const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			Minigin::m_DoContinue = false;
		}
		//if (e.type == SDL_KEYDOWN)
		//{
		//	//Cache the current key
		//	auto currentKey = e.key.keysym.scancode;

		//	//Stop running the program on Escape
		//	if (currentKey == SDLK_ESCAPE)
		//		Minigin::m_DoContinue = false;
		//}
	}
	for (std::pair<const int, std::pair<InputAction, std::shared_ptr<Command>>>& element : m_pButtons)
	{
		if (keyboardState[element.second.first.m_KeyboardCode])
		{
			if (element.second.first.m_CurrentTriggerState == InputTriggerState::Idle || element.second.first.m_CurrentTriggerState == InputTriggerState::Released)
			{
				element.second.first.m_CurrentTriggerState = InputTriggerState::Pressed;
			}

			else if (element.second.first.m_CurrentTriggerState == InputTriggerState::Pressed)
			{
				/*if (element.second.first.m_RequiredTriggerState == InputTriggerState::Pressed)
				{
					element.second.first.m_CurrentTriggerState = InputTriggerState::Idle;
				}*/
				/*if (element.second.first.m_RequiredTriggerState == InputTriggerState::Down)
			   {*/
				element.second.first.m_CurrentTriggerState = InputTriggerState::Down;
				//}
			}
		}
		else {
			if (element.second.first.m_CurrentTriggerState == InputTriggerState::Pressed || element.second.first.m_CurrentTriggerState == InputTriggerState::Down)
			{
				element.second.first.m_CurrentTriggerState = InputTriggerState::Released;
			}
			else if (element.second.first.m_CurrentTriggerState == InputTriggerState::Released)
			{
				element.second.first.m_CurrentTriggerState = InputTriggerState::Idle;
			}
		}
	}
}

//bool dae::InputManager::IsKeyPressed(int key, bool prevFrame) const
//{
//	if (!prevFrame)
//		return  (KBcurrentState[key] != 0);
//	else
//		return  (KBpreviousState[key] != 0);
//}

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