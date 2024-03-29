#pragma once

namespace dae {
	enum class MovementDirection
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	enum class CharacterState
	{
		Idle = 0,
		Move = 0,
		Action = 1,
		Die = 2
	};

	class GameObject;
	class Character
	{
	public:
		Character(std::string name, std::string imagePath, int rows, int cols, int startRow = 0);
		~Character() = default;

		void Init();
		void Update();
		void Die();

		bool GetIsDead() const { return m_IsDead; }

		std::shared_ptr<GameObject> GetCharacter() const
		{
			return m_pCharacter;
		}

		void SetCharacterState(CharacterState newState)
		{
			m_CharacterState = newState;
		}
	private:
		std::shared_ptr<GameObject> m_pCharacter;

		MovementDirection m_MovDir = MovementDirection::Right;
		CharacterState m_CharacterState;

		std::string m_Name, m_PathName;
		int m_Rows, m_Cols, m_StartRow;

		bool m_IsDead = false;
	};
}
