#pragma once
#include "TextureComponent.h"
#include <SDL.h>
#include "BaseComponent.h"
#include "glm/ext/vector_float2.hpp"

namespace dae {
	class SpriteComponent final : public dae::BaseComponent
	{
	public:
		SpriteComponent(std::shared_ptr<TextureComponent>  textureComp, int rows, int cols, int totalFrames);
		virtual ~SpriteComponent();

		void Update() override;

		void SetFlipHorizontal(bool newState)
		{
			m_FlipHorizontal = newState;
		}
		void SetFlipVertical(bool newState)
		{
			m_FlipVertical = newState;
		}
		bool IsFlippedHorizontal() const { return m_FlipHorizontal; }
		bool IsFlippedVertical() const { return m_FlipVertical; }

		const glm::vec2& GetOffset() const { return m_Offset; }
		void SetOffset(glm::vec2 newOffset)
		{
			m_Offset.x = newOffset.x;
			m_Offset.y = newOffset.y;
		}

		void SetRectToDraw(SDL_Rect rectToDraw)
		{
			m_RectToDraw = rectToDraw;
		}

		const SDL_Rect& GetRectToDraw()const
		{
			return m_RectToDraw;
		}

		void SetTexture(std::shared_ptr<TextureComponent> textureComp)
		{
			m_pTextureComp = textureComp;
		}

		std::shared_ptr<TextureComponent> GetTextureComp() const
		{
			return m_pTextureComp;
		}
	private:
		std::shared_ptr<TextureComponent> m_pTextureComp;
		bool m_FlipHorizontal = false;
		bool m_FlipVertical = false;
		glm::vec2 m_Offset;
		SDL_Rect m_RectToDraw;
	};
};
