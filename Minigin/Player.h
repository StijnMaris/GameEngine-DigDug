#pragma once
#include "Character.h"
namespace dae {
	class Player :public Character
	{
	public:
		Player(std::string name, std::string imagePath, int rows, int cols, int startRow = 0);
		~Player() = default;

		void DoAction()override;
	};
}
