#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace  dae {
	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(std::shared_ptr<TextComponent> textComponent);
		virtual ~FPSComponent() = default;

		void Update() override;
	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
	};
}
