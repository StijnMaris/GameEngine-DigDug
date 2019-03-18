#include "MiniginPCH.h"
#include "Time.h"

void dae::Time::Update()
{
	m_FrameCounter++;
	m_CurrentTime = GetTheCurrentTime();
	SetDeltaTime(std::chrono::duration<float>(m_CurrentTime - m_LastTime).count());

	if (m_DeltaTime > 1)
	{
		m_Fps = m_FrameCounter;
		m_FrameCounter = 0;
	}
	m_LastTime = m_CurrentTime;
}

float dae::Time::GetDeltaTime()const
{
	return m_DeltaTime;
}

std::chrono::time_point<std::chrono::steady_clock> dae::Time::GetTheCurrentTime()const
{
	return std::chrono::high_resolution_clock::now();
}

int dae::Time::GetFps()const
{
	return m_Fps;
}

void dae::Time::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}