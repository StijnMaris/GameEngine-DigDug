#pragma once
#include "BaseComponent.h"

namespace dae {
	class TextureComponent;
	class Font;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() = default;

		void Update() override;

		void SetText(const std::string& text);
		void CreateTextTexture();
		std::shared_ptr<TextureComponent>  GetTextureComponent() const;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<TextureComponent> m_pTextureComponent;
	};
}
