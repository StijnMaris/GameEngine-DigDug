#pragma once

namespace dae {
	class GameObject;
	class Character;
	class LevelScene;
	class Command : public std::enable_shared_from_this<Command>
	{
	public:
		Command() = default;
		Command(std::shared_ptr<GameObject> character) :m_pOwner(character) {}
		virtual ~Command() {}
		virtual bool execute() = 0;
		void AddToCommandStream();
	protected:
		std::shared_ptr<GameObject> m_pOwner;
	};

	//character comands
	class CharacterCommand : public Command
	{
	public:
		CharacterCommand(std::shared_ptr<Character> character);
		virtual bool execute() = 0;
	protected:
		std::shared_ptr<Character> m_pCharacter;
	};

	class RunLeftCommand : public CharacterCommand
	{
	public:
		RunLeftCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class RunRightCommand : public CharacterCommand
	{
	public:
		RunRightCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class RunUpCommand : public CharacterCommand
	{
	public:
		RunUpCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class RunDownCommand : public CharacterCommand
	{
	public:
		RunDownCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class ActionCommand : public CharacterCommand
	{
	public:
		ActionCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class StopActionCommand : public CharacterCommand
	{
	public:
		StopActionCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	//misc
	class ResetCommand : public CharacterCommand
	{
	public:
		ResetCommand(std::shared_ptr<LevelScene> Level, std::shared_ptr<Character> character) :
			CharacterCommand(character),
			m_pLevel(Level) {}
		bool execute() override;
	protected:
		std::shared_ptr<LevelScene> m_pLevel;
	};

	class ExitCommand : public CharacterCommand
	{
	public:
		ExitCommand(std::shared_ptr<Character> character) : CharacterCommand(character) {}
		bool execute() override;
	};
}
