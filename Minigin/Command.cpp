#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
//#include "Locator.h"

bool JumpCommand::execute()
{
	std::cout << "jump" << "\n";
	return true;
	//Locator::getAudio().playSound(0);
}

bool FireCommand::execute()
{
	std::cout << "Fire" << "\n";
	return true;
	//Locator::getAudio().playSound(1);
}

bool FartCommand::execute()
{
	std::cout << "Fart" << "\n";
	return true;
	//Locator::getAudio().playSound(2);
}

bool DuckCommand::execute()
{
	std::cout << "Duck" << "\n";
	return true;
	//Locator::getAudio().playSound(3);
}

bool ExitCommand::execute()
{
	std::cout << "Exit" << "\n";
	return false;
}