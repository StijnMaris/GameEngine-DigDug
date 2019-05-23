#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"

namespace dae {
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(std::shared_ptr<TextureComponent> textureComponent);
		RenderComponent(std::shared_ptr<SpriteComponent> sprite);
		virtual ~RenderComponent() = default;

		void Update()override {};

		void Render()const;
	private:
		std::shared_ptr<TextureComponent> m_pTextureComponent;
		std::shared_ptr<SpriteComponent> m_pSpriteComponent;

		bool m_IsSprite;
	};
}
