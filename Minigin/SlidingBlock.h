#pragma once
#include "GridBlock.h"

namespace dae {
	class SlidingBlock : public dae::GridBlock
	{
	public:
		SlidingBlock(glm::vec3 pos, dae::MovementDirection movDir, int row, int col, dae::BlockColor color, bool destroyed = false);
		~SlidingBlock();

		void Init()override;

		MovementDirection GetMovementDirection() const
		{
			return m_MovementDirection;
		}

	private:
		dae::MovementDirection m_MovementDirection;
	};
}
