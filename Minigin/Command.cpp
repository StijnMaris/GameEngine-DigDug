#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include "GameObject.h"
#include "Minigin.h"
#include "CommandComponent.h"
#include "MovementComponent.h"
#include "ActionComponent.h"
#include "Character.h"
#include "LevelScene.h"
//#include "Locator.h"

void dae::Command::AddToCommandStream()
{
	//m_pOwner->GetPosition();
	m_pOwner->GetComponent<CommandComponent>()->AddCommand(shared_from_this());
}

dae::CharacterCommand::CharacterCommand(std::shared_ptr<Character> character, std::shared_ptr<LevelScene> Level) :m_pCharacter(character), m_pLevel(Level)
{
	m_pOwner = character->GetCharacter();
}

bool dae::RunLeftCommand::execute()
{
	//std::cout << "Left" << "\n";
	m_pCharacter->SetCharacterState(CharacterState::Move);
	m_pCharacter->SetMovementDirection(MovementDirection::Left);
	m_pCharacter->GetCharacter()->GetComponent<MovementComponent>()->MoveLeft(m_pLevel->GetGridSystem());
	return true;
	//Locator::getAudio().playSound(0);
}

bool dae::RunRightCommand::execute()
{
	//std::cout << "Right" << "\n";
	m_pCharacter->SetCharacterState(CharacterState::Move);
	m_pCharacter->SetMovementDirection(MovementDirection::Right);
	m_pCharacter->GetCharacter()->GetComponent<MovementComponent>()->MoveRight(m_pLevel->GetGridSystem());
	return true;
	//Locator::getAudio().playSound(1);
}

bool dae::RunUpCommand::execute()
{
	//std::cout << "Up" << "\n";
	m_pCharacter->SetCharacterState(CharacterState::Move);
	m_pCharacter->SetMovementDirection(MovementDirection::Up);
	m_pCharacter->GetCharacter()->GetComponent<MovementComponent>()->MoveUp(m_pLevel->GetGridSystem());
	return true;
	//Locator::getAudio().playSound(2);
}

bool dae::RunDownCommand::execute()
{
	//std::cout << "Down" << "\n";
	m_pCharacter->SetCharacterState(CharacterState::Move);
	m_pCharacter->SetMovementDirection(MovementDirection::Down);
	m_pCharacter->GetCharacter()->GetComponent<MovementComponent>()->MoveDown(m_pLevel->GetGridSystem());
	return true;
	//Locator::getAudio().playSound(3);
}

bool dae::ActionCommand::execute()
{
	//std::cout << "Action" << "\n";
	m_pCharacter->SetCharacterState(CharacterState::Action);
	m_pCharacter->GetCharacter()->GetComponent<ActionComponent>()->DoAction(m_pLevel->GetGridSystem(), m_pCharacter->GetMovementDirection());
	return true;
}

bool dae::StopActionCommand::execute()
{
	m_pCharacter->SetCharacterState(CharacterState::Idle);
	return true;
}

bool dae::ResetCommand::execute()
{
	m_pLevel->Reset();
	return true;
}

//misc
bool dae::ExitCommand::execute()
{
	Minigin::m_DoContinue = false;
	std::cout << "Exit" << "\n";
	return false;
}