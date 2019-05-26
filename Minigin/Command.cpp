#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include "GameObject.h"
#include "Minigin.h"
#include "CommandComponent.h"
#include "MovementComponent.h"
#include "ActionComponent.h"
//#include "Locator.h"

void dae::Command::AddToCommandStream()
{
	//m_pOwner->GetPosition();
	m_pOwner->GetComponent<CommandComponent>()->AddCommand(shared_from_this());
}

bool dae::RunLeftCommand::execute()
{
	//std::cout << "Left" << "\n";
	m_pOwner->GetComponent<MovementComponent>()->MoveDown();
	return true;
	//Locator::getAudio().playSound(0);
}

bool dae::RunRightCommand::execute()
{
	//std::cout << "Right" << "\n";
	m_pOwner->GetComponent<MovementComponent>()->MoveDown();
	return true;
	//Locator::getAudio().playSound(1);
}

bool dae::RunUpCommand::execute()
{
	//std::cout << "Up" << "\n";
	m_pOwner->GetComponent<MovementComponent>()->MoveDown();
	return true;
	//Locator::getAudio().playSound(2);
}

bool dae::RunDownCommand::execute()
{
	//std::cout << "Down" << "\n";
	m_pOwner->GetComponent<MovementComponent>()->MoveDown();
	return true;
	//Locator::getAudio().playSound(3);
}

bool dae::ActionCommand::execute()
{
	std::cout << "Action" << "\n";
	m_pOwner->GetComponent<ActionComponent>()->DoAction();
	return true;
}

//misc
bool dae::ExitCommand::execute()
{
	Minigin::m_DoContinue = false;
	std::cout << "Exit" << "\n";
	return false;
}