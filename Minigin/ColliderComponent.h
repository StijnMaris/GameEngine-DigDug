#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <glm/vec3.hpp>

namespace  dae {
	class Transform;
	class ColliderComponent final : public BaseComponent
	{
	public:
		ColliderComponent(std::shared_ptr<Transform> transform, SDL_Rect rect);
		virtual ~ColliderComponent();

		void Update() override;
		void SetColliderRect(SDL_Rect rect);

		SDL_Rect GetCollider() const
		{
			return  m_Collider;
		}

	private:
		SDL_Rect m_Collider;
		glm::vec3 m_PrevPosition;

		std::shared_ptr<Transform> m_pTransformComponent;
	};
}
