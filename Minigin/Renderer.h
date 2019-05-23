#pragma once
#include "Singleton.h"
#include <glm/vec3.hpp>
#include <SDL.h>
#include "SpriteComponent.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const glm::vec3& pos) const;
		void RenderTexture(const Texture2D& texture, const glm::vec3& pos, const SDL_Rect& srcRect) const;
		void RenderTexture(const Texture2D& texture, std::shared_ptr<SpriteComponent> spriteComp) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}
