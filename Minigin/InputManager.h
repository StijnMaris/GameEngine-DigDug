#pragma once
#include <XInput.h>
#include "Command.h"
#include <memory>
#include "Singleton.h"
#include <map>
#include <glm/vec2.hpp>
#include <SDL.h>

namespace dae
{
	enum class GamepadIndex : DWORD
	{
		PlayerOne = 0,
		PlayerTwo = 1,
		Menu = 2,
	};

	enum class InputTriggerState
	{
		Pressed = 0,
		Down = 1,
		Released = 2,
		Idle = 3
	};
	struct InputAction
	{
		InputAction() :
			m_ActionID("default"),
			m_RequiredTriggerState(InputTriggerState::Pressed),
			m_KeyboardCode(SDL_SCANCODE_UNKNOWN),
			m_MouseButtonCode(-1),
			m_GamepadButtonCode(0),
			m_PlayerIndex(GamepadIndex::PlayerOne),
			m_IsTriggered(false),
			m_CurrentTriggerState(InputTriggerState::Idle) {}

		InputAction(std::string& actionID, InputTriggerState requiredTriggerState = InputTriggerState::Pressed,
			SDL_Scancode keyboardCode = SDL_SCANCODE_UNKNOWN, int mouseButtonCode = -1, WORD gamepadButtonCode = 0,
			GamepadIndex playerIndex = GamepadIndex::PlayerOne,
			bool isTriggered = false, InputTriggerState currentTriggerState = InputTriggerState::Idle) :
			m_ActionID(actionID),
			m_RequiredTriggerState(requiredTriggerState),
			m_KeyboardCode(keyboardCode),
			m_MouseButtonCode(mouseButtonCode),
			m_GamepadButtonCode(gamepadButtonCode),
			m_PlayerIndex(playerIndex),
			m_IsTriggered(isTriggered),
			m_CurrentTriggerState(currentTriggerState) {}

		std::string m_ActionID;
		InputTriggerState m_RequiredTriggerState;
		SDL_Scancode m_KeyboardCode;
		int m_MouseButtonCode;
		WORD m_GamepadButtonCode; //XINPUT_GAMEPAD_...
		GamepadIndex m_PlayerIndex;
		bool m_IsTriggered;
		InputTriggerState m_CurrentTriggerState;
	};

	class Gamepad
	{
	public:
		Gamepad(const unsigned int playerId);
		~Gamepad() = default;

		friend class InputManager;

		//BUTTONS
		const InputTriggerState GetButtonState(WORD button) const;
		bool WasPressed(WORD button) const;
		bool IsPressed(WORD button) const;

	private:
		XINPUT_STATE currentState;		// the state of the gamepad in the current frame
		XINPUT_STATE previousState;		// the state of the game in the previous frame
		const unsigned int playerID;	// player number (0-3)

		glm::vec2 m_ThumbStickL;
		glm::vec2 m_ThumbStickR;

		bool checkConnection();
		void GetState();
		void GetFixedThumbStick(glm::vec2& thumbStick, bool isLeft = true);
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		void ProcessInput();
		void HandleInput();
		void Init();

		//bool AddInputAction(InputAction action);

		//bool IsPressed(InputAction button) const;

		void MapInput(InputAction button, std::shared_ptr<Command> command);
		void RefreshInput();

	private:
		bool InitGamepads();
		void ProcessKeyboardInput();
		void ProcessGamePadInput();

		bool IsActionTriggered(int actionID);

		//const InputTriggerState GetKeystrokeState(int key) const;
		//bool IsKeyPressed(int key, bool prevFrame = false) const;

		void RefreshControllerConnections();

		const glm::vec2 getLStick() const;
		const glm::vec2 getRStick() const;

		glm::vec2 GetThumbstickPosition(bool leftThumbstick = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne);
		float GetTriggerPressure(bool leftTrigger = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne);
		void SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex = GamepadIndex::PlayerOne);

		bool IsGamepadConnected(GamepadIndex index) const;

		//variables
		std::map<int, std::pair<InputAction, std::shared_ptr<Command>> > m_pButtons;

		bool m_IsInitialized = false;

		bool m_UseGamepad = false;
		bool m_UseKeyboard = true;

		//Keyboad and mouse
		bool m_KBstate0InUse = false;
		POINT m_MouseXY;

		//GAMEPADS
		std::vector<std::shared_ptr<Gamepad>> m_pGamePads;
		std::shared_ptr<Gamepad> m_pCurrentGamePad;
		unsigned int m_CurrentlyActivePlayer;
		unsigned int m_NrGamepads;
		unsigned int m_NrPlayers = 1;

		XINPUT_STATE currentState{}, previousState{};

		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		InputManager(const InputManager& t) = delete;
		InputManager& operator=(const InputManager& t) = delete;
	};
}
