#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <glm/vec3.hpp>
#include "Transform.h"
#include <glm/vec2.hpp>

namespace  dae {
	class ColliderComponent final : public BaseComponent
	{
	public:
		ColliderComponent(glm::vec2 pos, int width, int height);
		virtual ~ColliderComponent();

		void Update() override;
		void SetColliderRect(glm::vec2 pos, int width, int height);

	private:
		SDL_Rect m_Collider;
		glm::vec3 m_PrevPosition;

		std::shared_ptr<Transform> m_pTransformComponent;
	};
}
