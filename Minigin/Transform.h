#pragma once
#include <glm/vec3.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:

		Transform(glm::vec3 pos = { 0,0,0 }, glm::vec3 scale = { 1,1,1 });
		virtual ~Transform() = default;

		void Update() override {};
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(glm::vec3 pos = { 0,0,0 });
		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z = 1);
		void SetScale(glm::vec3 scale = { 1,1,1 });

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
	};
}
