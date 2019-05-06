#pragma once
class Command
{
public:
	virtual ~Command() {}
	virtual bool execute() = 0;
};

class JumpCommand : public Command
{
public:
	bool execute() override;
};

class FireCommand : public Command
{
public:
	bool execute() override;
};

class FartCommand : public Command
{
public:
	bool execute() override;
};

class DuckCommand : public Command
{
public:
	bool execute() override;
};

class ExitCommand : public Command
{
public:
	bool execute() override;
};
