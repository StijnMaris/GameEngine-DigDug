#pragma once
namespace dae {
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() {}
		virtual bool execute(GameObject actor) = 0;
	};

	class RunLeftCommand : public Command
	{
	public:
		bool execute(GameObject actor) override;
	};

	class RunRightCommand : public Command
	{
	public:
		bool execute(GameObject actor) override;
	};

	class RunUpCommand : public Command
	{
	public:
		bool execute(GameObject actor) override;
	};

	class RunDownCommand : public Command
	{
	public:
		bool execute(GameObject actor) override;
	};

	class ExitCommand : public Command
	{
	public:
		bool execute(GameObject actor) override;
	};
}
