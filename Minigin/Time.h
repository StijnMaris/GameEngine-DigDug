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
		std::chrono::time_point<std::chrono::high_resolution_clock> GetTheCurrentTime()const;
		int GetFps()const;

	private:
		void SetDeltaTime(float deltaTime);

		int m_Fps, m_TotalFrames;
		float m_DeltaTime, m_TotalTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime, m_CurrentTime;
	};
}
