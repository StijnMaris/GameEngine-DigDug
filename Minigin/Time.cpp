#include "MiniginPCH.h"
#include "Time.h"

using namespace std::chrono;

void dae::Time::Update()
{
	m_CurrentTime = GetTheCurrentTime();
	SetDeltaTime(duration<float>(m_CurrentTime - m_LastTime).count());
	m_TotalTime += GetDeltaTime();

	m_TotalFrames++;
	if (static_cast<int>(m_TotalTime) % 1 != 0) {}
	else
	{
		m_Fps = static_cast<int>(1.f / GetDeltaTime());
	}

	m_LastTime = m_CurrentTime;
}

float dae::Time::GetDeltaTime()const
{
	return m_DeltaTime;
}

float dae::Time::GetTotalTime() const
{
	return m_TotalTime;
}

time_point<high_resolution_clock> dae::Time::GetTheCurrentTime()const
{
	return high_resolution_clock::now();
}

int dae::Time::GetFps()const
{
	return m_Fps;
}

void dae::Time::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}