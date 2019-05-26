#pragma once
#include <vector>

namespace dae {
	enum class Event { WhiteBlockDestroyed, YellowBlockDestroyed, PinkBlockDestroyed, RedBlockDestroyed };
	class Observer
	{
	public:

		virtual ~Observer() {}
		virtual void onNotify(Event event) = 0;
		//virtual void onNotify(Event event, int damage, int health) = 0;
	};

	//class HealthDisplay : public Observer
	//{
	//public:
	//	virtual void onNotify(Event event)
	//	{
	//		event;
	//	}
	//	/*void onNotify(Event event, int damage, int health)override
	//	{
	//		switch (event)
	//		{
	//		case Event::HealthChange:
	//			std::cout << "Player Health is: " << health << "\n";
	//			if (damage >= 20)
	//			{
	//				notify(Event::BigHealthChange);
	//			}
	//			if (health <= 0)
	//			{
	//				notify(Event::GameOver);
	//			}
	//			break;
	//		}
	//	}*/

	//	void addObserver(Observer* observer)
	//	{
	//		m_pObservers.push_back(observer);
	//		m_numObservers++;
	//	}
	//	void removeObserver(Observer* observer)
	//	{
	//		m_pObservers.erase(std::find(m_pObservers.begin(), m_pObservers.end(), observer));
	//		m_numObservers--;
	//	}
	//protected:
	//	void notify(Event event)
	//	{
	//		for (int i = 0; i < m_numObservers; i++)
	//		{
	//			m_pObservers[i]->onNotify(event);
	//		}
	//	}
	//private:
	//	std::vector<Observer*> m_pObservers;
	//	int m_numObservers;
	//};

	class Score : public Observer
	{
	public:
		/*virtual void onNotify(Event event, int damage, int health)
		{
			event;
			damage;
			health;
		}*/
		void onNotify(Event event)override
		{
			switch (event)
			{
			case Event::WhiteBlockDestroyed:
				m_Score += 100;
				break;

			case Event::YellowBlockDestroyed:
				m_Score += 200;
				break;
			case Event::PinkBlockDestroyed:
				m_Score += 300;
				break;
			case Event::RedBlockDestroyed:
				m_Score += 400;
				break;
				/*case Event::GameOver:
					std::cout << "GameOver" << "\n";
					break;*/
			}
		}
		static int m_Score;
	private:
		/*void Unlock(Achievement& achievement)
		{
			if (!achievement.IsAchievementUnlocked())
			{
				achievement.Unlock();
			}
		}

		Achievement m_Skippy{ "Skyppy" }, m_Sneeky{ "Sneeky" }, m_Player{ "Player" }, m_Ouch{ "Ouch" };
		int m_Jumps{}, m_Ducks{}, m_Plays{};*/
	};
}