#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>

#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
		glm::vec3 m_Position;
	public:

		Transform();
		virtual ~Transform() = default;

		void Update() override {};
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	};
}
