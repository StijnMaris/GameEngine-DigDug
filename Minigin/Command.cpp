#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include  "GameObject.h"
//#include "Locator.h"

bool dae::RunLeftCommand::execute()
{
	std::cout << "jump" << "\n";
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

bool dae::ExitCommand::execute()
{
	std::cout << "Exit" << "\n";
	return false;
}