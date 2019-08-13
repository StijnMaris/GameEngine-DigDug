#pragma once
#include "BaseComponent.h"
#include <SDL.h>

namespace  dae {
	class Transform;
	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent(std::shared_ptr<Transform> transform, SDL_Rect rect);
		~MovementComponent();

		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		void Update() override;

	private:
		std::shared_ptr<Transform> m_pTransform;
		SDL_Rect m_Rect;

		SDL_Rect m_BoundRect;

		float m_MovementsizeH,m_MovementsizeW;
		int m_GridMovConstraintW,m_GridMovConstraintH;
	};
}
