#pragma once
#include "Singleton.h"
#include <chrono>
namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		//Time() = default;
		void Update();

		float GetDeltaTime()const;
		std::chrono::time_point<std::chrono::steady_clock> GetTheCurrentTime()const;
		int GetFps()const;

	private:
		void SetDeltaTime(float deltaTime);

		int m_FrameCounter, m_Fps;
		float m_DeltaTime;
		std::chrono::time_point<std::chrono::steady_clock> m_LastTime, m_CurrentTime;
	};
}
