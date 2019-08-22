#pragma once
#include "BaseComponent.h"
//#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <SDL.h>

namespace  dae {
	class GridSystem;
	class Transform;
	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent(std::shared_ptr<Transform> transform, SDL_Rect rect);
		~MovementComponent() = default;

		void MoveUp(std::shared_ptr<GridSystem> grid);
		void MoveDown(std::shared_ptr<GridSystem> grid);
		void MoveLeft(std::shared_ptr<GridSystem> grid);
		void MoveRight(std::shared_ptr<GridSystem> grid);
		void Update() override;

		void SetPosition(glm::vec3 newPos);

	private:
		std::shared_ptr<Transform> m_pTransform;
		SDL_Rect m_Rect;

		glm::vec3 m_StartPos;
		glm::vec3 m_Destination;

		float m_MovementSpeed;

		int m_Accuracy;

		/*SDL_Rect m_BoundRect;

		float m_MovementsizeH, m_MovementsizeW;*/
		int m_GridMovConstraintW, m_GridMovConstraintH;
	};
}
