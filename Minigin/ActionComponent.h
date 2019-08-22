#pragma once
#include "BaseComponent.h"

namespace dae {
	enum class MovementDirection;
	class GridSystem;
	class Transform;

	class ActionComponent :public BaseComponent
	{
	public:
		ActionComponent(std::shared_ptr<Transform> transform);
		~ActionComponent() = default;

		void DoAction(std::shared_ptr<GridSystem> grid, MovementDirection movDir);

		void Update() override {}

	private:
		std::shared_ptr<Transform> m_pTransform;
	};
}
