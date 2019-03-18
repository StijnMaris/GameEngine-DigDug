#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"

namespace dae {
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(std::shared_ptr<TextureComponent> textureComponent);
		virtual ~RenderComponent() = default;

		void Update()override {};

		void Render(float posX, float posY)const;
	private:
		std::shared_ptr<TextureComponent> m_pTextureComponent;
	};
}
