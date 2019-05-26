#include "MiniginPCH.h"
#include "GridSystem.h"
#include "GridBlock.h"
#include "GameObject.h"
#include "Renderer.h"
#include <glm/vec2.hpp>
#include "Scene.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "CommandComponent.h"

dae::GridSystem::GridSystem(int rows, int cols) :m_Rows(rows), m_Columns(cols)
{
	m_pGridSystem = std::make_shared<GameObject>("GridSystem");
}

void dae::GridSystem::Init()
{
	m_StartPos = m_pGridSystem->GetPosition();
	SetUpGrid();
	for (size_t i = 0; i < m_Columns; i++)
	{
		for (int j = 0; j < m_Rows; j++)
		{
			m_pBlocks[i][j]->Init();
			m_pBlocks[i][j]->GetBlock()->SetScale(2, 2);
		}
	}

	m_pPlayer = std::make_shared<GameObject>("Player");
	m_pPlayer->Init();
	m_pPlayer->SetPosition(200, 180);
	m_pPlayer->SetScale(2, 2);
	m_pPlayer->AddComponent(std::make_shared<TextureComponent>("DigDug.png"));
	m_pPlayer->AddComponent(std::make_shared<SpriteComponent>(m_pPlayer->GetComponent<TextureComponent>(), 2, 4, 0, true, 200));
	m_pPlayer->AddComponent(std::make_shared<RenderComponent>(m_pPlayer->GetComponent<SpriteComponent>()));
	m_pPlayer->AddComponent(std::make_shared<CommandComponent>());
	m_pPlayer->AddComponent(std::make_shared<ColliderComponent>(m_pPlayer->GetComponent<Transform>(), m_pPlayer->GetComponent<SpriteComponent>()->GetRectToDraw()));
}

void dae::GridSystem::Draw() const
{
	////Debug render the cells
	//for (int i = 0; i < m_Rows; i++)
	//{
	//	for (int j = 0; j < m_Columns; j++)
	//	{
	//		if (GetCellState(i, j))
	//		{
	//			Renderer::GetInstance().DrawSquareAroundCenter(GetCellPosition(i, j), m_CellSize / 2.f, Color(255, 0, 0, 255));
	//		}
	//		else
	//		{
	//			Renderer::GetInstance().DrawSquareAroundCenter(GetCellPosition(i, j), m_CellSize / 2.f, Color(0, 255, 0, 255));
	//		}
	//	}
	//}
}

void dae::GridSystem::Reset()
{
	m_Grid.clear();
	for (int i = 0; i < m_pBlocks.size(); ++i)
	{
		m_pBlocks[i].clear();
	}
	m_pBlocks.clear();
}

void dae::GridSystem::AddToScene(Scene& scene)
{
	for (size_t i = 0; i < m_Columns; i++)
	{
		for (int j = 0; j < m_Rows; j++)
		{
			scene.AddGameObject(m_pBlocks[i][j]->GetBlock());
		}
	}
}

void dae::GridSystem::SetUpGrid()
{
	m_Grid.clear();
	m_Grid.resize(m_Columns);
	for (int i = 0; i < m_Columns; i++)
	{
		m_Grid[i].resize(m_Rows);
	}
	int divi = m_Rows / 5;
	for (int i = 0; i < m_Columns; i++)
	{
		for (int j = 0; j < m_Rows; ++j)
		{
			if (i < divi)
			{
				m_Grid[i][j] = false;
			}
			else {
				m_Grid[i][j] = true;
			}
		}
	}

	m_pBlocks.clear();
	m_pBlocks.resize(m_Columns);
	for (int i = 0; i < m_Columns; i++)
	{
		m_pBlocks[i].resize(m_Rows);
	}

	int color = 1;
	for (int i = 0; i < m_Columns; i++)
	{
		/*if ((i + 1) % (divi + 1) == 0)
		{
			color++;
		}*/
		color = 1;
		for (int j = 0; j < m_Rows; ++j)
		{
			color = j / divi + 1;

			m_pBlocks[i][j] = std::make_shared<GridBlock>(glm::vec3{ m_StartPos.x + i * m_CellSize, m_StartPos.y + j * m_CellSize,0 }, i, j, static_cast<BlockColor>(color));
		}
	}
}

bool dae::GridSystem::GetCellState(int row, int col) const
{
	if (row < 0)
		return true;
	if (row > m_Rows - 1)
		return true;

	if (col < 0)
		return true;
	if (col > m_Columns - 1)
		return true;

	return m_Grid[row][col];
}

bool dae::GridSystem::GetCellState(std::pair<int, int> cellData) const
{
	return GetCellState(cellData.first, cellData.second);
}

bool dae::GridSystem::GetCellState(glm::vec3 position) const
{
	int row, col;
	GetCellData(position, row, col);
	return GetCellState(row, col);
}

void dae::GridSystem::SetCellState(int row, int col, bool newState)
{
	m_Grid[row][col] = newState;
}

void dae::GridSystem::SetCellState(glm::vec3 position, bool newState)
{
	int row, col;
	GetCellData(position, row, col);
	SetCellState(row, col, newState);
}

void dae::GridSystem::SetCellState(std::shared_ptr<GridBlock> newBlock)
{
	const auto blockPos = newBlock->GetBlock()->GetPosition();
	SetCellState(blockPos, true);
	m_pBlocks[newBlock->GetRow()][newBlock->GetColumn()] = newBlock;
}

glm::vec3 dae::GridSystem::GetCellPosition(int row, int height) const
{
	return glm::vec3(row * m_CellSize + m_CellSize / 2.f, height * m_CellSize + m_CellSize / 2.f, 0.f);
}

glm::vec3 dae::GridSystem::GetCellPosition(std::pair<int, int> cellData) const
{
	return GetCellPosition(cellData.first, cellData.second);
}

glm::vec3 dae::GridSystem::GetCellPosition(const glm::vec3& position) const
{
	int row, col;
	GetCellData(position, row, col);
	return GetCellPosition(row, col);
}

void dae::GridSystem::GetCellData(const glm::vec3 position, int& row, int& col) const
{
	//Find the nearest Grid X Position
	{
		const int remainder = int(position.x) % m_CellSize;
		row = (static_cast<int>(position.x) - remainder) / m_CellSize;
	}

	//Find the nearest Grid X Position
	{
		const int remainder = int(position.y) % m_CellSize;
		col = (static_cast<int>(position.y) - remainder) / m_CellSize;
	}
}

std::pair<int, int> dae::GridSystem::GetCellData(const glm::vec3 position) const
{
	int row, col;
	//Find the nearest Grid X Position
	{
		const int remainder = int(position.x) % m_CellSize;
		row = (static_cast<int>(position.x) - remainder) / m_CellSize;
	}

	//Find the nearest Grid X Position
	{
		const int remainder = int(position.y) % m_CellSize;
		col = (static_cast<int>(position.y) - remainder) / m_CellSize;
	}
	return std::make_pair(row, col);
}

void dae::GridSystem::GetCellData(const std::shared_ptr<GridBlock> block, int& row, int& col) const
{
	auto position = glm::vec2{ 2,2 };
	UNREFERENCED_PARAMETER(block);
	//= block->GetParent()->GetTransform()->GetPosition();
	//Find the nearest Grid X Position
	{
		const int remainder = int(position.x) % m_CellSize;
		row = (static_cast<int>(position.x) - remainder) / m_CellSize;
	}

	//Find the nearest Grid X Position
	{
		const int remainder = int(position.y) % m_CellSize;
		col = (static_cast<int>(position.y) - remainder) / m_CellSize;
	}
}

bool dae::GridSystem::CanMoveInDirection(const glm::vec3& position, Direction dir)
{
	int row, col;
	GetCellData(position, row, col);

	//Check for actual blocks
	switch (dir)
	{
	case Direction::Up:
	{
		if (GetCellState(row, --col))
			return false;
		break;
	}
	case Direction::Down:
	{
		if (GetCellState(row, ++col))
			return false;
		break;
	}
	case Direction::Left:
	{
		if (GetCellState(--row, col))
			return false;
		break;
	}
	case Direction::Right:
	{
		if (GetCellState(++row, col))
			return false;
		break;
	}
	}
	return true;
}

bool dae::GridSystem::DestroyCell(int row, int col)
{
	return m_pBlocks[row][col]->Destroy();
}

float dae::GridSystem::GetDistanceBetween(glm::vec3 start, glm::vec3 end)
{
	return std::sqrtf(std::powf(end.x - start.x, 2) + std::powf(end.y - start.y, 2));
}

void dae::GridSystem::CheckForCollision()
{
	for (int i = 0; i < m_Columns; i++)
	{
		for (int j = 0; j < m_Rows; ++j)
		{
			auto collider = m_pPlayer->GetComponent<ColliderComponent>()->GetCollider();
			if (m_pBlocks[i][j]->CheckIfColliding(collider))
			{
				m_pBlocks[i][j]->SetBlockColor(BlockColor::Black);
			}
		}
	}
}