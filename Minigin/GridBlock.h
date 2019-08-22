#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#include <SDL.h>

namespace dae {
	enum class BlockColor
	{
		Empty = 0,
		Ice = 1,
		Egg = 2,
		Diamond = 3,
		Wall = 4
	};
	enum class MovementDirection;
	class GameObject;
	class GridBlock
	{
	public:
		GridBlock(glm::vec3 pos, int row, int col, BlockColor color, bool destroyed = false);
		virtual ~GridBlock();

		void Init();
		int GetRow() const { return m_Row; }
		int GetColumn() const { return m_Col; }

		std::shared_ptr<GameObject> GetBlock() const
		{
			return m_pBlock;
		}

		bool Destroy();

		bool IsDestroyed() const { return m_Destroyed; }

		BlockColor GetBlockColor() const
		{
			return m_Color;
		}

		void SetBlockColor(BlockColor color);

		bool CheckIfColliding(SDL_Rect& otherRect) const;

		void Slide(MovementDirection& Direction);

	private:
		std::shared_ptr<GameObject> m_pBlock;

		glm::vec3 m_Pos;
		int m_Row;
		int m_Col;
		BlockColor  m_Color;
		bool m_Destroyed = false, m_HasCollision = true;
	};
}
