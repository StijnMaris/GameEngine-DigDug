#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include "GameObject.h"
#include "Minigin.h"
#include "CommandComponent.h"
//#include "Locator.h"

dae::Command::Command(std::shared_ptr<GameObject> character)
{
	m_pOwner = character;
}

dae::CharacterCommand::CharacterCommand(std::shared_ptr<GameObject> character) : Command(character)
{
}

void dae::Command::AddToCommandStream()
{
	//m_pOwner->GetPosition();
	m_pOwner->GetComponent<CommandComponent>()->AddCommand(shared_from_this());
}

dae::RunLeftCommand::RunLeftCommand(std::shared_ptr<GameObject> character) : CharacterCommand(character)
{
}

bool dae::RunLeftCommand::execute()
{
	std::cout << "jump" << "\n";

	m_pOwner->SetPosition(m_pOwner->GetPosition().x + 10, m_pOwner->GetPosition().y, m_pOwner->GetPosition().z);

	return true;
	//Locator::getAudio().playSound(0);
}

bool dae::RunRightCommand::execute()
{
	std::cout << "Fire" << "\n";
	return true;
	//Locator::getAudio().playSound(1);
}

bool dae::RunUpCommand::execute()
{
	std::cout << "Fart" << "\n";
	return true;
	//Locator::getAudio().playSound(2);
}

bool dae::RunDownCommand::execute()
{
	std::cout << "Duck" << "\n";
	return true;
	//Locator::getAudio().playSound(3);
}

//misc
bool dae::ExitCommand::execute()
{
	Minigin::m_DoContinue = false;
	std::cout << "Exit" << "\n";
	return false;
}