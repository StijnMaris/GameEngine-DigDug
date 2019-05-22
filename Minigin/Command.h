#pragma once
namespace dae {
	class GameObject;

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
		CharacterCommand(std::shared_ptr<GameObject> character) : Command(character) {}
		virtual bool execute() = 0;
	};

	class RunLeftCommand : public CharacterCommand
	{
	public:
		RunLeftCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class RunRightCommand : public CharacterCommand
	{
	public:
		RunRightCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class RunUpCommand : public CharacterCommand
	{
	public:
		RunUpCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class RunDownCommand : public CharacterCommand
	{
	public:
		RunDownCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	class ActionCommand : public CharacterCommand
	{
	public:
		ActionCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character) {}
		bool execute() override;
	};

	//misc
	class ExitCommand : public CharacterCommand
	{
	public:
		ExitCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character) {}
		bool execute() override;
	};
}
