#pragma once
//#include "Block.h"
#include <glm/vec3.hpp>
#include "Character.h"

namespace  dae {
	class Scene;
	class GridBlock;

	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	enum class CellDefinition
	{
		Normal = 0,
		Empty = 1,
		Player1 = 2,
		Player2 = 3,
		VSPlayer2 = 4,
		Pooka = 5,
		Fygar = 6,
		Rock = 7
	};

	class GameObject;
	class Player;
	class GridSystem final
	{
	public:
		GridSystem(int rows, int cols);

		void Init();

		void Update();
		void Draw() const;
		void Reset();

		void AddToScene(Scene& scene);

		void SetUpGrid();

		bool GetCellState(int row, int col) const;
		bool GetCellState(std::pair<int, int> cellData) const;
		bool GetCellState(glm::vec3 position) const;

		void SetCellState(int row, int col, bool newState);
		void SetCellState(glm::vec3 position, bool newState);
		void SetCellState(std::shared_ptr<GridBlock> newBlock);
		void SetCellState(int row, int col, CellDefinition cellDef);

		glm::vec3 GetCellPosition(int row, int height) const;
		glm::vec3 GetCellPosition(std::pair<int, int> cellData) const;
		glm::vec3 GetCellPosition(const glm::vec3& position) const;

		void GetCellData(const glm::vec3 position, int& row, int& col) const;
		std::pair<int, int> GetCellData(const glm::vec3 position) const;
		void GetCellData(const std::shared_ptr<GridBlock> block, int& row, int&col) const;
		bool CanMoveInDirection(const glm::vec3& position, Direction dir);

		bool DestroyCell(int row, int column);

		float GetDistanceBetween(glm::vec3 start, glm::vec3 end);

		int GetCellSize() const
		{
			return m_CellSize;
		}
		int GetGridWith() const
		{
			return m_CellSize * m_Rows;
		}
		int GetGridHeight() const
		{
			return m_CellSize * m_Columns;
		}

		std::shared_ptr<GameObject> GetGridSystem() const
		{
			return m_pGridSystem;
		}

		std::shared_ptr<Character> GetPlayer() const
		{
			return m_pPlayer1;
		}

		void CheckForCollision();

		void LoadMap(std::string path);

		void DefineMap();

	private:
		std::shared_ptr<GameObject> m_pGridSystem;
		std::shared_ptr<Character>  m_pPlayer1;

		std::vector<std::vector<bool>> m_Grid;
		std::vector<std::vector<CellDefinition>> m_GridDefinition;
		std::vector<std::vector<std::shared_ptr<GridBlock>>> m_pBlocks;

		glm::vec3 m_StartPos{};
		int m_CellSize = 32;
		int m_Rows = 0;
		int m_Columns = 0;
	};
}
