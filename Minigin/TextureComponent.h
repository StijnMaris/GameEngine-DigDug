#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae {
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename);
		virtual ~TextureComponent() = default;

		void Update() {};

		void SetTexture(const std::string& filename);
		std::shared_ptr<Texture2D>  GetTexture();
	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}
