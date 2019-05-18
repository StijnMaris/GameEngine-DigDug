#pragma once
namespace dae {
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() {}
		virtual bool execute() = 0;
	};

	class RunLeftCommand : public Command
	{
	public:
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

	class ExitCommand : public Command
	{
	public:
		bool execute() override;
	};
}
