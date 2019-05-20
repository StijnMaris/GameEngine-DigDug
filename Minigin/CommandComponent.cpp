#include "MiniginPCH.h"
#include "CommandComponent.h"

dae::CommandComponent::CommandComponent() :BaseComponent("CommandComponent")
{
}

void dae::CommandComponent::Update()
{
}

void dae::CommandComponent::AddCommand(std::shared_ptr<Command> pCommand)
{
	m_Commands.push(pCommand);
}