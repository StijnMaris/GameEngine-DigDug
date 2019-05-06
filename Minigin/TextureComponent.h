#pragma once
#include "BaseComponent.h"
#include <SDL.h>

namespace dae {
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename);
		TextureComponent(SDL_Texture* texture);
		virtual ~TextureComponent() = default;

		void Update()override {};

		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);
		std::shared_ptr<Texture2D>  GetTexture()const;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
