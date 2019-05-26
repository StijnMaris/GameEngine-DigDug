// Observers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MiniginPCH.h"
#include <iostream>

#include "Observer.h"

int dae::Score::m_Score = 0;

//int main()
//{
//	/*auto* achievements = new Achievements();
//	auto* hpDisplay = new HealthDisplay();
//	auto* player = new Player(100);*/
//	player->addObserver(achievements);
//	player->addObserver(hpDisplay);
//	hpDisplay->addObserver(achievements);
//	for (int round = 0; round < 8; ++round)
//	{
//		for (int i = 0; i < 12; ++i)
//		{
//			player->Jump();
//			player->Duck();
//			player->TakeDamage(5);
//		}
//		player->TakeDamage(30);
//		player->TakeDamage(10);
//		player->Reset(100);
//	}
//	std::cin.get();
//	delete player;
//}