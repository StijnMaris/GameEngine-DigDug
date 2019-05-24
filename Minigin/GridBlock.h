#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>

namespace dae {
	enum class BlockColor
	{
		Black = 0,
		Blue = 1,
		White = 2,
		Yellow = 3,
		Pink = 4,
		Red = 5
	};
	class GridBlock
	{
	public:
		GridBlock(glm::vec3 pos, int row, int col, BlockColor color, bool hasCollision, bool destroyed = false);
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

	private:
		std::shared_ptr<GameObject> m_pBlock;

		glm::vec3 m_Pos;
		int m_Row;
		int m_Col;
		BlockColor  m_Color;
		bool m_Destroyed = false, m_HasCollision = true;
	};
}
