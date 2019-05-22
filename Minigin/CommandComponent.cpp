#include "MiniginPCH.h"
#include "CommandComponent.h"

dae::CommandComponent::CommandComponent() :BaseComponent("CommandComponent")
{
}

void dae::CommandComponent::Update()
{
	while (m_Commands.size() > 0)
	{
		m_Commands.front()->execute();
		m_Commands.pop();
	}
}

void dae::CommandComponent::AddCommand(std::shared_ptr<Command> pCommand)
{
	m_Commands.push(pCommand);
}