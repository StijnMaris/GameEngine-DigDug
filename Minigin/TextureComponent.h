#pragma once
#include "BaseComponent.h"

namespace dae {
	class TextComponent;
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename);
		TextureComponent(const std::shared_ptr<TextComponent> textComponent);
		virtual ~TextureComponent() = default;

		void Update()override;

		void SetTexture(const std::string& filename);
		std::shared_ptr<Texture2D>  GetTexture()const;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<TextComponent> m_pTextComponent;
	};
}
