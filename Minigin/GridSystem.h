#pragma once
#include <glm/vec3.hpp>

namespace  dae {
	enum class BlockColor;
	enum class Event;
	enum class MovementDirection;
	class Observer;
	class Scene;
	class GridBlock;
	class Character;
	class Scene;
	class GameObject;
	class Player;
	class SlidingBlock;

	enum class CellDefinition
	{
		Normal = 0,
		Empty = 1,
		Player1 = 2,
		Player2 = 3,
		VSPlayer2 = 4,
		SnoBee = 5,
		Egg = 6,
		Diamond = 7,
		Wall = 8,
	};

	class GridSystem final :public std::enable_shared_from_this<GridSystem>
	{
	public:
		GridSystem(int rows, int cols, std::string& filePath, std::shared_ptr<Scene> scene);

		void Init();

		void Update();
		void Draw() const;
		void Reset();
		void Restart();

		void AddToScene(std::shared_ptr<GameObject> object)const;
		void RemoveFromScene(std::shared_ptr<GameObject> object)const;

		void SetUpGrid();

		bool GetCellState(int row, int col) const;
		bool GetCellState(std::pair<int, int> cellData) const;
		bool GetCellState(glm::vec3& position) const;

		void SetCellState(int row, int col, bool newState);
		void SetCellState(glm::vec3& position, bool newState);
		void SetCellState(std::shared_ptr<GridBlock> newBlock);
		void SetCellState(int row, int col, CellDefinition cellDef);

		glm::vec3 GetCellPosition(int row, int height) const;
		glm::vec3 GetCellPosition(std::pair<int, int> cellData) const;
		glm::vec3 GetCellPosition(const glm::vec3& position) const;

		void GetCellData(glm::vec3 position, int& row, int& col) const;
		std::pair<int, int> GetCellData(const glm::vec3& position) const;
		void GetCellData(std::shared_ptr<GridBlock> block, int& row, int&col) const;

		std::shared_ptr<GridBlock> GetGridBlockAtPosition(int row, int col) const;
		std::shared_ptr<GridBlock> GetGridBlockAtPosition(std::pair<int, int> cellData) const;
		std::shared_ptr<GridBlock> GetGridBlockAtPosition(glm::vec3& position) const;

		bool CanMoveInDirection(const glm::vec3& position, MovementDirection dir);
		std::pair<int, int>  GetNeighboringBlockInDirection(const glm::vec3& position, MovementDirection& dir);

		bool IsAccesingBlockOutsideOfGrid(int row, int col)const;

		bool DestroyBlock(int row, int col);

		float GetDistanceBetween(glm::vec3& start, glm::vec3& end);

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

		std::shared_ptr<Character> GetPlayer(std::string name);

		void SlideBlockInDirection(const glm::vec3& position, MovementDirection& dir, BlockColor& color);
		void UpdateSlidingBlocks();
		void CheckForCollision();

		void AddGridToScene();

		void addObserver(std::shared_ptr<Observer> observer);
		void removeObserver(std::shared_ptr<Observer> observer);

	protected:
		void notify(Event event);

	private:

		void DefineMap();
		void LoadMap(std::string& path);
		bool DestroyCell(int row, int col);

		void SpawnPlayer(glm::vec3& pos, std::string& name, std::string& file, bool isFriendly);
		void SpawnEnemy(glm::vec3& pos, std::string& name, std::string& file, bool isFriendly);

		std::shared_ptr<GameObject> m_pGridSystem;
		std::vector<std::shared_ptr<Character>>  m_pPlayers;

		std::vector<std::vector<bool>> m_Grid;
		std::vector<std::vector<CellDefinition>> m_GridDefinition;
		std::vector<std::vector<std::shared_ptr<GridBlock>>> m_pBlocks;

		std::vector<std::shared_ptr<SlidingBlock>> m_pSlidingBlocks;

		std::vector<std::shared_ptr<Character>> m_pEnemies;

		glm::vec3 m_GridStartPos{};
		glm::vec3 m_Player1StartPos{};
		glm::vec3 m_Player2StartPos{};
		glm::vec3 m_PlayerVSStartPos{};
		int m_CellSize = 32;
		int m_Rows = 0;
		int m_Columns = 0;
		int m_ResetCounter;

		std::weak_ptr<Scene> m_Scene;

		std::vector<std::shared_ptr<Observer>> m_pObservers;
		int m_numObservers;

		std::string m_FilePath;
		std::string m_P1Name, m_P2Name, m_PVSName;
		std::string m_P1File, m_P2File, m_PVSFile;
	};
}
