#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "GameObject.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const glm::vec3& pos) const
{
	RenderTexture(texture, pos.x, pos.y);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const glm::vec3& pos, const SDL_Rect& srcRect) const
{
	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(pos.x);
	dstRect.y = static_cast<int>(pos.y);
	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, std::shared_ptr<SpriteComponent> spriteComp) const
{
	SDL_Rect dst;

	dst.w = int(static_cast<float>(spriteComp->GetSpriteWidth()) * spriteComp->GetOwner()->GetScale().x);
	dst.h = int(static_cast<float>(spriteComp->GetSpriteHeight()) * spriteComp->GetOwner()->GetScale().y);

	//Rotation Center
	SDL_Point center;
	center.x = int(dst.w * spriteComp->GetOffset().x);
	center.y = int(dst.h * spriteComp->GetOffset().y);

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (spriteComp->IsFlippedHorizontal() && !spriteComp->IsFlippedVertical())
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (spriteComp->IsFlippedVertical() && !spriteComp->IsFlippedHorizontal())
	{
		flip = SDL_FLIP_VERTICAL;
	}
	else if (spriteComp->IsFlippedHorizontal() && spriteComp->IsFlippedVertical())
	{
		flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}

	//Find The Position The Texture Needs To Be Drawn At
	dst.x = static_cast<int>(spriteComp->GetOwner()->GetPosition().x);
	dst.y = static_cast<int>(spriteComp->GetOwner()->GetPosition().y);
	dst.x -= int(dst.w * spriteComp->GetOffset().x);
	dst.y -= int(dst.h * spriteComp->GetOffset().y);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &(spriteComp->GetRectToDraw()), &dst, 0, &center, flip);
}