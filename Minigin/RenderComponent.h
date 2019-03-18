#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"

namespace dae {
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent();
		virtual ~RenderComponent() = default;

		void Update() {};

		void Render(float posX, float posY)const;
	private:
		std::shared_ptr<TextureComponent> m_Texture;
	};
}
