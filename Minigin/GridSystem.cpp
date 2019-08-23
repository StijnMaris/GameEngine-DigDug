#include "MiniginPCH.h"
#include "GridSystem.h"
#include "GridBlock.h"
#include "GameObject.h"
#include "Renderer.h"
#include <glm/vec2.hpp>
#include "Scene.h"
#include "ColliderComponent.h"
//#include "RenderComponent.h"
//#include "CommandComponent.h"
#include <fstream>
#include "Observer.h"

dae::GridSystem::GridSystem(int rows, int cols, std::string filePath) :m_Rows(rows), m_Columns(cols), m_FilePath(filePath), m_numObservers(0)
{
	m_pGridSystem = std::make_shared<GameObject>("GridSystem");
	m_pPlayer1 = std::make_shared<Character>("Player1", "DigDug.png", 3, 4);
}

void dae::GridSystem::Init()
{
	m_GridStartPos = m_pGridSystem->GetPosition();
	SetUpGrid();
	for (size_t i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; j++)
		{
			m_pBlocks[i][j]->Init();
			m_pBlocks[i][j]->GetBlock()->SetScale(2, 2);
		}
	}
	DefineMap();

	m_pPlayer1->Init();
	m_pPlayer1->SetPosition(m_Player1StartPos);
}

void dae::GridSystem::Update()
{
	m_pPlayer1->Update();
}

void dae::GridSystem::Draw() const
{
	////Debug render the cells
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; j++)
		{
			if (GetCellState(i, j))
			{
				Renderer::GetInstance().DrawSquareAroundCenter(GetCellPosition(i, j), (float)m_CellSize);
			}
			else
			{
				Renderer::GetInstance().DrawSquareAroundCenter(GetCellPosition(i, j), (float)m_CellSize);
			}
		}
	}
	auto rect = m_pPlayer1->GetCharacter()->GetComponent<ColliderComponent>()->GetCollider();
	std::cout << "x: " << rect.x << " y: " << rect.y << std::endl;
	Renderer::GetInstance().DrawSquareAroundCenter(glm::vec3{ rect.x,rect.y,0 }, (float)/*m_CellSize*/rect.w);
}

void dae::GridSystem::Reset()
{
	m_pPlayer1->SetPosition(m_Player1StartPos);

	int divi = m_Columns / 5;
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			int color = j / divi + 1;

			m_pBlocks[i][j]->SetBlockColor(static_cast<BlockColor>(color));
		}
	}
	DefineMap();
}

void dae::GridSystem::AddToScene(Scene& scene)
{
	for (size_t i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; j++)
		{
			scene.AddGameObject(m_pBlocks[i][j]->GetBlock());
		}
	}
}

void dae::GridSystem::SetUpGrid()
{
	m_Grid.clear();
	m_Grid.resize(m_Rows);
	for (int i = 0; i < m_Rows; i++)
	{
		m_Grid[i].resize(m_Columns);
		std::fill(m_Grid[i].begin(), m_Grid[i].end(), true);
	}

	m_pBlocks.clear();
	m_pBlocks.resize(m_Rows);
	for (int i = 0; i < m_Rows; i++)
	{
		m_pBlocks[i].resize(m_Columns);
	}

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			BlockColor color = BlockColor::Ice;

			m_pBlocks[i][j] = std::make_shared<GridBlock>(glm::vec3{ m_GridStartPos.x + j * m_CellSize, m_GridStartPos.y + i * m_CellSize,0 }, i, j, color);
		}
	}

	m_GridDefinition.resize(m_Rows);
	for (int i = 0; i < m_Rows; i++)
	{
		m_GridDefinition[i].resize(m_Columns);
	}
	LoadMap(m_FilePath);
}

bool dae::GridSystem::GetCellState(int row, int col) const
{
	if (IsAccesingBlockOutsideOfGrid(row, col))
	{
		return true;
	}
	return m_Grid[row][col];
}

bool dae::GridSystem::GetCellState(std::pair<int, int> cellData) const
{
	return GetCellState(cellData.first, cellData.second);
}

bool dae::GridSystem::GetCellState(glm::vec3& position) const
{
	int row, col;
	GetCellData(position, row, col);
	return GetCellState(row, col);
}

void dae::GridSystem::SetCellState(int row, int col, bool newState)
{
	m_Grid[row][col] = newState;
}

void dae::GridSystem::SetCellState(glm::vec3& position, bool newState)
{
	int row, col;
	GetCellData(position, row, col);
	SetCellState(row, col, newState);
}

void dae::GridSystem::SetCellState(std::shared_ptr<GridBlock> newBlock)
{
	auto blockPos = newBlock->GetBlock()->GetPosition();
	SetCellState(blockPos, true);
	m_pBlocks[newBlock->GetRow()][newBlock->GetColumn()] = newBlock;
}

void dae::GridSystem::SetCellState(int row, int col, CellDefinition cellDef)
{
	m_GridDefinition[row][col] = (cellDef);
}

glm::vec3 dae::GridSystem::GetCellPosition(int row, int height) const
{
	return glm::vec3(m_pBlocks[row][height]->GetBlock()->GetComponent<ColliderComponent>()->GetCollider().x, m_pBlocks[row][height]->GetBlock()->GetComponent<ColliderComponent>()->GetCollider().y, 0.f);
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
		const int remainder = int(position.y) % m_CellSize;
		row = (static_cast<int>(position.y) - remainder) / m_CellSize;
	}

	//Find the nearest Grid Y Position
	{
		const int remainder = int(position.x) % m_CellSize;
		col = (static_cast<int>(position.x) - remainder) / m_CellSize;
	}
}

std::pair<int, int> dae::GridSystem::GetCellData(const glm::vec3& position) const
{
	int row, col;
	GetCellData(position, row, col);
	return std::make_pair(row, col);
}

void dae::GridSystem::GetCellData(const std::shared_ptr<GridBlock> block, int& row, int& col) const
{
	auto position = block->GetBlock()->GetPosition();
	GetCellData(position, row, col);
}

std::shared_ptr<dae::GridBlock> dae::GridSystem::GetGridBlockAtPosition(int row, int col) const
{
	return m_pBlocks[row][col];
}

std::shared_ptr<dae::GridBlock> dae::GridSystem::GetGridBlockAtPosition(std::pair<int, int> cellData) const
{
	return GetGridBlockAtPosition(cellData.first, cellData.second);
}

std::shared_ptr<dae::GridBlock> dae::GridSystem::GetGridBlockAtPosition(glm::vec3& position) const
{
	int row, col;
	GetCellData(position, row, col);
	return GetGridBlockAtPosition(row, col);
}

bool dae::GridSystem::CanMoveInDirection(const glm::vec3& position, MovementDirection dir)
{
	int row, col;
	GetCellData(position, row, col);

	//Check for actual blocks

	switch (dir)
	{
	case MovementDirection::Up:
	{
		if (GetCellState(--row, col))
			return false;

		break;
	}
	case MovementDirection::Down:
	{
		if (GetCellState(++row, col))
			return false;

		break;
	}
	case MovementDirection::Left:
	{
		if (GetCellState(row, --col))
			return false;

		break;
	}
	case MovementDirection::Right:
	{
		if (GetCellState(row, ++col))
			return false;

		break;
	}
	default:
	{
		return false;
	}
	}
	return true;
}

std::pair<int, int>  dae::GridSystem::GetNeighboringBlockInDirection(const glm::vec3& position, MovementDirection& dir)
{
	int row, col;
	GetCellData(position, row, col);
	switch (dir)
	{
	case MovementDirection::Up:
	{
		if (!IsAccesingBlockOutsideOfGrid(--row, col))
			return std::pair<int, int>{row, col};
	}
	case MovementDirection::Down:
	{
		if (!IsAccesingBlockOutsideOfGrid(++row, col))
			return std::pair<int, int>{row, col};
	}
	case MovementDirection::Left:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, --col))
			return std::pair<int, int>{row, col};
	}
	case MovementDirection::Right:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, ++col))
			return std::pair<int, int>{row, col};
	}
	default:
		return std::pair<int, int>{-1, -1};
	}
}

bool dae::GridSystem::IsAccesingBlockOutsideOfGrid(int row, int col)const
{
	if (row < 0)
		return true;
	if (row > m_Rows - 1)
		return true;

	if (col < 0)
		return true;
	if (col > m_Columns - 1)
		return true;
	return false;
}

bool dae::GridSystem::DestroyCell(int row, int col)
{
	m_Grid[row][col] = false;
	/*if (m_pBlocks[row][col]->GetBlockColor() == BlockColor::White)
	{
		notify(Event::WhiteBlockDestroyed);
	}
	else if (m_pBlocks[row][col]->GetBlockColor() == BlockColor::Yellow)
	{
		notify(Event::YellowBlockDestroyed);
	}
	else if (m_pBlocks[row][col]->GetBlockColor() == BlockColor::Pink)
	{
		notify(Event::PinkBlockDestroyed);
	}
	else if (m_pBlocks[row][col]->GetBlockColor() == BlockColor::Red)
	{
		notify(Event::RedBlockDestroyed);
	}*/

	return m_pBlocks[row][col]->Destroy();
}

float dae::GridSystem::GetDistanceBetween(glm::vec3& start, glm::vec3& end)
{
	return std::sqrtf(std::powf(end.x - start.x, 2) + std::powf(end.y - start.y, 2));
}

void dae::GridSystem::SlideBlockInDirection(const glm::vec3& position, MovementDirection& dir)
{
	int row, col;
	GetCellData(position, row, col);

	switch (dir)
	{
	case MovementDirection::Up:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, col)) {
			auto block = std::make_shared<GridBlock>(glm::vec3{ position.x, position.y,0 }, -1, -1, BlockColor::Egg);
			block->Init();
			DestroyCell(row, col);
		}
	}
	case MovementDirection::Down:
	{
		//if (!IsAccesingBlockOutsideOfGrid(++row, col))
			//return std::pair<int, int>{row, col};
	}
	case MovementDirection::Left:
	{
		//if (!IsAccesingBlockOutsideOfGrid(row, --col))
			//return std::pair<int, int>{row, col};
	}
	case MovementDirection::Right:
	{
		//if (!IsAccesingBlockOutsideOfGrid(row, ++col))
			//return std::pair<int, int>{row, col};
	}
	default:
		break;
		//return std::pair<int, int>{-1, -1};
	}
}

void dae::GridSystem::CheckForCollision()
{
	/*for (int i = 0; i < m_Columns; i++)
	{
		for (int j = 0; j < m_Rows; ++j)
		{
			auto collider = m_pPlayer->GetComponent<ColliderComponent>()->GetCollider();
			if (m_pBlocks[i][j]->CheckIfColliding(collider))
			{
				m_pBlocks[i][j]->Destroy();
			}
		}
	}*/

	auto collider = m_pPlayer1->GetCharacter()->GetComponent<ColliderComponent>()->GetCollider();
	auto gridPos = GetCellData(m_pPlayer1->GetCharacter()->GetPosition());
	if (m_pBlocks[gridPos.first][gridPos.second]->CheckIfColliding(collider))
	{
		m_pBlocks[gridPos.first][gridPos.second]->Destroy();
		m_Grid[gridPos.first][gridPos.second] = false;
	}
	/*else if (gridPos.first - 1 >= 0 && gridPos.first + 1 < m_Rows && gridPos.first - 1 >= 0 && gridPos.first + 1 < m_Columns)
	{
		if (m_pBlocks[gridPos.first + 1][gridPos.second]->CheckIfColliding(collider))
		{
			m_pBlocks[gridPos.first + 1][gridPos.second]->Destroy();
		}
		else if (m_pBlocks[gridPos.first - 1][gridPos.second]->CheckIfColliding(collider))
		{
			m_pBlocks[gridPos.first - 1][gridPos.second]->Destroy();
		}
		else if (m_pBlocks[gridPos.first][gridPos.second + 1]->CheckIfColliding(collider))
		{
			m_pBlocks[gridPos.first][gridPos.second + 1]->Destroy();
		}
		else if (m_pBlocks[gridPos.first][gridPos.second - 1]->CheckIfColliding(collider))
		{
			m_pBlocks[gridPos.first][gridPos.second - 1]->Destroy();
		}
	}*/
}

void dae::GridSystem::LoadMap(std::string& path)
{
	char tile;
	std::ifstream mapFile(path);

	if (!mapFile)
	{
		std::cout << "Opening Map File Failed" << std::endl;
	}
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			mapFile.get(tile);
			if (i == 0 || j == 0 || i == m_Rows - 1 || j == m_Columns - 1)
			{
				SetCellState(i, j, CellDefinition::Wall);
				mapFile.ignore();
			}
			else
			{
				SetCellState(i, j, static_cast<CellDefinition>(std::atoi(&tile)));
				mapFile.ignore();
			}
		}
	}
	mapFile.close();
}

void dae::GridSystem::DefineMap()
{
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			switch (m_GridDefinition[i][j])
			{
			case CellDefinition::Normal:
				m_pBlocks[i][j]->SetBlockColor(BlockColor::Ice);
				break;
			case CellDefinition::Empty:
				DestroyCell(i, j);
				break;
			case CellDefinition::Player1:
				DestroyCell(i, j);
				glm::vec3 pos = GetCellPosition(i, j);
				pos.x += 16;
				pos.y += 16;
				m_Player1StartPos = pos;
				break;
			case CellDefinition::Player2:
				DestroyCell(i, j);
				break;
			case CellDefinition::VSPlayer2:
				DestroyCell(i, j);
				break;
			case CellDefinition::SnoBee:
				DestroyCell(i, j);
				break;
			case CellDefinition::Egg:
				m_pBlocks[i][j]->SetBlockColor(BlockColor::Egg);
				break;

			case CellDefinition::Diamond:
				m_pBlocks[i][j]->SetBlockColor(BlockColor::Diamond);
				break;

			case CellDefinition::Wall:
				m_pBlocks[i][j]->SetBlockColor(BlockColor::Wall);
				break;
			}
		}
	}
}

void dae::GridSystem::addObserver(std::shared_ptr<Observer> observer)
{
	m_pObservers.push_back(observer);
	m_numObservers++;
}

void dae::GridSystem::removeObserver(std::shared_ptr<Observer> observer)
{
	m_pObservers.erase(std::find(m_pObservers.begin(), m_pObservers.end(), observer));
	m_numObservers--;
}

void dae::GridSystem::notify(Event event)
{
	for (int i = 0; i < m_numObservers; i++)
	{
		m_pObservers[i]->onNotify(event);
	}
}