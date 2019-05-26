#include "MiniginPCH.h"
#include "Player.h"

dae::Player::Player(std::string name, std::string imagePath, int rows, int cols, int startRow) :
	Character(name, imagePath, rows, cols, startRow)
{
}

void dae::Player::DoAction()
{
}