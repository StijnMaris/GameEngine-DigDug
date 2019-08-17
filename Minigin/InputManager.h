#pragma once
#include <XInput.h>
#include "Command.h"
#include <memory>
#include "Singleton.h"
#include <map>
#include <glm/vec2.hpp>

namespace dae
{
	enum class GamepadIndex : DWORD
	{
		PlayerOne = 0,
		PlayerTwo = 1,
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
			ActionID(-1),
			TriggerState(InputTriggerState::Pressed),
			KeyboardCode(-1),
			MouseButtonCode(-1),
			GamepadButtonCode(0),
			PlayerIndex(GamepadIndex::PlayerOne),
			IsTriggered(false) {}

		InputAction(int actionID, InputTriggerState triggerState = InputTriggerState::Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne) :
			ActionID(actionID),
			TriggerState(triggerState),
			KeyboardCode(keyboardCode),
			MouseButtonCode(mouseButtonCode),
			GamepadButtonCode(gamepadButtonCode),
			PlayerIndex(playerIndex),
			IsTriggered(false) {}

		int ActionID;
		InputTriggerState TriggerState;
		int KeyboardCode; //VK_... (Range 0x07 <> 0xFE)
		int MouseButtonCode; //VK_... (Range 0x00 <> 0x06)
		WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
		GamepadIndex PlayerIndex;
		bool IsTriggered;
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

	private:
		bool InitGamepads();
		void ProcessKeyboardInput();
		void ProcessGamePadInput();

		void RefreshInput();

		bool IsActionTriggered(int actionID);

		const InputTriggerState GetKeystrokeState(int key) const;
		bool IsKeyPressed(int key, bool prevFrame = false) const;

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
		std::vector<bool> KBcurrentState, KBpreviousState;
		bool KBstate0InUse = false;
		POINT mouseXY;

		//GAMEPADS
		std::vector<std::shared_ptr<Gamepad>> m_pGamePads;
		std::shared_ptr<Gamepad> m_pCurrentGamePad;
		unsigned int currentlyActivePlayer;
		unsigned int nGamepads;
		unsigned int nPlayers = 1;

		XINPUT_STATE currentState{}, previousState{};

		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		InputManager(const InputManager& t) = delete;
		InputManager& operator=(const InputManager& t) = delete;
	};
}
