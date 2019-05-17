#pragma once
#include <XInput.h>
#include "Command.h"
#include <memory>
#include "Singleton.h"
#include <map>
#include <glm/vec2.hpp>

namespace dae
{
	enum GamepadIndex : DWORD
	{
		PlayerOne = 0,
		PlayerTwo = 1,
	};

	enum InputTriggerState
	{
		Pressed,
		Released,
		Down
	};
	struct InputAction
	{
		InputAction() :
			ActionID(-1),
			TriggerState(Pressed),
			KeyboardCode(-1),
			MouseButtonCode(-1),
			GamepadButtonCode(0),
			PlayerIndex(PlayerOne),
			IsTriggered(false) {}

		InputAction(int actionID, InputTriggerState triggerState = Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = PlayerOne) :
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

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		void HandleInput();
		bool IsPressed(InputAction button) const;

		void MapInput(InputAction button, std::shared_ptr<Command> command);

	private:
		bool IsActionTriggered(int actionID);
		static void SetEnabled(bool enabled) { m_Enabled = enabled; }

		void RefreshControllerConnections();
		POINT GetMousePosition(bool previousFrame = false) const { return (previousFrame) ? m_OldMousePosition : m_CurrMousePosition; }
		POINT GetMouseMovement() const { return m_MouseMovement; }
		bool IsKeyboardKeyDown(int key, bool previousFrame = false);
		bool IsMouseButtonDown(int button, bool previousFrame = false);
		bool IsGamepadButtonDown(WORD button, GamepadIndex playerIndex = GamepadIndex::PlayerOne, bool previousFrame = false);

		glm::vec2 GetThumbstickPosition(bool leftThumbstick = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne);
		float GetTriggerPressure(bool leftTrigger = true, GamepadIndex playerIndex = GamepadIndex::PlayerOne);
		void SetVibration(float leftVibration, float rightVibration, GamepadIndex playerIndex = GamepadIndex::PlayerOne);

		void CursorVisible(bool visible) { ShowCursor(visible); }
		bool IsGamepadConnected(GamepadIndex index) const { return m_ConnectedGamepads[(DWORD)index]; }

		void UpdateGamepadStates();
		bool UpdateKeyboardStates();
		//varuiables
		std::map<int, std::pair<InputAction, std::shared_ptr<Command>> > m_pButtons;

		static BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		static bool m_KeyboardState0Active;
		static POINT m_CurrMousePosition, m_OldMousePosition, m_MouseMovement;
		static bool m_IsInitialized;
		static bool m_Enabled;

		static XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT], m_CurrGamepadState[XUSER_MAX_COUNT];
		static bool m_ConnectedGamepads[XUSER_MAX_COUNT];

		// -------------------------
		// Disabling default copy constructor and default
		// assignment operator.
		// -------------------------
		InputManager(const InputManager& t) = delete;
		InputManager& operator=(const InputManager& t) = delete;
	};
}
