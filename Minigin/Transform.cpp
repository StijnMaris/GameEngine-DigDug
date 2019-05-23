#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform(glm::vec3 pos, glm::vec3 scale) :BaseComponent("Transform"), m_Position(pos), m_Scale(scale)
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
}

void dae::Transform::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

void dae::Transform::SetScale(glm::vec3 scale)
{
	m_Scale = scale;
}