#pragma once
namespace dae {
	class GameObject;

	class Command : public std::enable_shared_from_this<Command>
	{
	public:
		Command() = default;
		Command(std::shared_ptr<GameObject> character);
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
		CharacterCommand(std::shared_ptr<GameObject> character);
		virtual bool execute() = 0;
	};

	class RunLeftCommand : public CharacterCommand
	{
	public:
		RunLeftCommand(std::shared_ptr<GameObject> character);
		bool execute() override;
	};

	class RunRightCommand : public Command
	{
	public:
		bool execute() override;
	};

	class RunUpCommand : public Command
	{
	public:
		bool execute() override;
	};

	class RunDownCommand : public Command
	{
	public:
		bool execute() override;
	};

	//misc
	class ExitCommand : public Command
	{
	public:
		bool execute() override;
		//void AddToCommandStream() override {}
	};
}
