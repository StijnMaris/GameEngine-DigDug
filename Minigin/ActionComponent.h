#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>

namespace dae {
	enum class MovementDirection;
	class LevelScene;
	class Transform;

	class ActionComponent :public BaseComponent
	{
	public:
		ActionComponent(std::shared_ptr<Transform> transform);
		~ActionComponent() = default;

		void DoAction(std::shared_ptr<LevelScene> level, MovementDirection movDir);

		void Update() override {};

	private:
		std::shared_ptr<Transform> m_pTransform;
		glm::vec3 m_StartPos;
		glm::vec3 m_Destination;
	};
}
