#include "MiniginPCH.h"
#include "GridSystem.h"
#include "GridBlock.h"
#include "GameObject.h"
#include "Renderer.h"
#include <glm/vec2.hpp>
#include "Scene.h"
#include "ColliderComponent.h"
#include "Character.h"
//#include "Scene.h"
#include <fstream>
#include "Observer.h"
#include "SlidingBlock.h"
#include "MovementComponent.h"
#include <algorithm>

dae::GridSystem::GridSystem(int rows, int cols, std::string& filePath, std::shared_ptr<Scene> scene) :m_Rows(rows), m_Columns(cols), m_FilePath(filePath), m_Scene(scene), m_numObservers(0)
{
	m_pGridSystem = std::make_shared<GameObject>("GridSystem");
	m_P1Name = "Player1";
	m_P2Name = "Player2";
	m_P1File = "DigDug1.png";
	m_P2File = "DigDug2.png";

	m_GridDefinition.resize(m_Rows);
	for (int i = 0; i < m_Rows; i++)
	{
		m_GridDefinition[i].resize(m_Columns);
	}
	LoadMap(m_FilePath);
}

void dae::GridSystem::Init()
{
	m_GridStartPos = m_pGridSystem->GetPosition();
	SetUpGrid();
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; j++)
		{
			m_pBlocks[i][j]->Init();
			m_pBlocks[i][j]->GetBlock()->SetScale(2, 2);
		}
	}
	DefineMap();
	AddGridToScene();
}

void dae::GridSystem::Update()
{
	for (std::shared_ptr<Character> element : m_pPlayers)
	{
		element->Update();
	}
	UpdateSlidingBlocks();
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
	//			Renderer::GetInstance().DrawSquareAroundCenter(GetCellPosition(i, j), (float)m_CellSize);
	//		}
	//		else
	//		{
	//			Renderer::GetInstance().DrawSquareAroundCenter(GetCellPosition(i, j), (float)m_CellSize);
	//		}
	//	}
	//}
	//auto rect = m_pPlayer1->GetCharacter()->GetComponent<ColliderComponent>()->GetCollider();
	////std::cout << "x: " << rect.x << " y: " << rect.y << std::endl;
	//Renderer::GetInstance().DrawSquareAroundCenter(glm::vec3{ rect.x,rect.y,0 }, (float)/*m_CellSize*/rect.w);
}

void dae::GridSystem::Reset()
{
	m_ResetCounter++;
	GetPlayer("Player1")->SetPosition(m_Player1StartPos);
	GetPlayer("Player2")->SetPosition(m_Player2StartPos);
	if (m_ResetCounter == 3)
	{
		Restart();
	}
	//DefineMap();
}

void dae::GridSystem::Restart()
{
	for (const std::shared_ptr<Character> element : m_pPlayers)
	{
		RemoveFromScene(element->GetCharacter());
	}

	for (const std::shared_ptr<Character> element : m_pEnemies)
	{
		RemoveFromScene(element->GetCharacter());
	}

	for (const std::shared_ptr<SlidingBlock> element : m_pSlidingBlocks)
	{
		RemoveFromScene(element->GetBlock());
	}
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			RemoveFromScene(m_pBlocks[i][j]->GetBlock());
		}
	}
	RemoveFromScene(m_pGridSystem);
}

void dae::GridSystem::AddToScene(std::shared_ptr<GameObject> object)const
{
	std::shared_ptr<Scene> scene = m_Scene.lock();
	if (scene)
		scene->AddGameObject(object);
}

void dae::GridSystem::RemoveFromScene(std::shared_ptr<GameObject> object) const
{
	std::shared_ptr<Scene> scene = m_Scene.lock();
	if (scene)
		scene->RemoveGameObject(object);
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
		const int remainder = int(position.y - (m_GridStartPos.y - m_CellSize / 2)) % m_CellSize;
		row = (static_cast<int>(position.y - (m_GridStartPos.y - m_CellSize / 2)) - remainder) / m_CellSize;
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
	SetCellState(row, col, false);

	return m_pBlocks[row][col]->Destroy();
}

bool dae::GridSystem::DestroyBlock(int row, int col)
{
	switch (m_pBlocks[row][col]->GetBlockColor())
	{
	case BlockColor::Ice:
		notify(Event::IceBlockDestroyed);
		break;
	case BlockColor::Egg:
		notify(Event::EggBlockDestroyed);
		break;
	default:
		break;
	}

	/*else if (m_pBlocks[row][col]->GetBlockColor() == BlockColor::Pink)
	{
		notify(Event::PinkBlockDestroyed);
	}
	else if (m_pBlocks[row][col]->GetBlockColor() == BlockColor::Red)
	{
		notify(Event::RedBlockDestroyed);
	}*/

	return DestroyCell(row, col);
}

float dae::GridSystem::GetDistanceBetween(glm::vec3& start, glm::vec3& end)
{
	return std::sqrtf(std::powf(end.x - start.x, 2) + std::powf(end.y - start.y, 2));
}

std::shared_ptr<dae::Character> dae::GridSystem::GetPlayer(std::string name)
{
	for (std::shared_ptr<Character> element : m_pPlayers)
	{
		if (!element->GetName().compare(name))
		{
			return element;
		}
	}
	return nullptr;
}

void dae::GridSystem::SlideBlockInDirection(const glm::vec3& position, MovementDirection& dir, BlockColor& color)
{
	int row, col;
	GetCellData(position, row, col);

	switch (dir)
	{
	case MovementDirection::Up:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, col)) {
			DestroyCell(row, col);

			auto block = std::make_shared<SlidingBlock>(glm::vec3{ position.x, position.y,0 }, MovementDirection::Up, row, col, color);
			block->Init();
			AddToScene(block->GetBlock());
			m_pSlidingBlocks.push_back(block);
		}
		break;
	}
	case MovementDirection::Down:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, col)) {
			DestroyCell(row, col);

			auto block = std::make_shared<SlidingBlock>(glm::vec3{ position.x, position.y,0 }, MovementDirection::Down, row, col, color);
			block->Init();
			AddToScene(block->GetBlock());
			m_pSlidingBlocks.push_back(block);
		}
		break;
	}
	case MovementDirection::Left:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, col)) {
			DestroyCell(row, col);

			auto block = std::make_shared<SlidingBlock>(glm::vec3{ position.x, position.y,0 }, MovementDirection::Left, row, col, color);
			block->Init();
			AddToScene(block->GetBlock());
			m_pSlidingBlocks.push_back(block);
		}
		break;
	}
	case MovementDirection::Right:
	{
		if (!IsAccesingBlockOutsideOfGrid(row, col)) {
			DestroyCell(row, col);

			auto block = std::make_shared<SlidingBlock>(glm::vec3{ position.x, position.y,0 }, MovementDirection::Right, row, col, color);
			block->Init();
			AddToScene(block->GetBlock());
			m_pSlidingBlocks.push_back(block);
		}
		break;
	}
	default:
		break;
	}
}

void dae::GridSystem::UpdateSlidingBlocks()
{
	for (std::shared_ptr<SlidingBlock> element : m_pSlidingBlocks)
	{
		if (CanMoveInDirection(element->GetBlock()->GetPosition(), element->GetMovementDirection()))
		{
			switch (element->GetMovementDirection())
			{
			case MovementDirection::Up:
				element->GetBlock()->GetComponent<MovementComponent>()->MoveUp(shared_from_this());
				break;
			case MovementDirection::Down:
				element->GetBlock()->GetComponent<MovementComponent>()->MoveDown(shared_from_this());
				break;
			case MovementDirection::Left:
				element->GetBlock()->GetComponent<MovementComponent>()->MoveLeft(shared_from_this());
				break;
			case MovementDirection::Right:
				element->GetBlock()->GetComponent<MovementComponent>()->MoveRight(shared_from_this());
				break;
			}
		}
		else
		{
			RemoveFromScene(element->GetBlock());
			m_pSlidingBlocks.erase(std::remove(m_pSlidingBlocks.begin(), m_pSlidingBlocks.end(), element), m_pSlidingBlocks.end());
			auto pos = element->GetBlock()->GetPosition();
			SetCellState(pos, true);
			GetGridBlockAtPosition(pos)->SetBlockColor(element->GetBlockColor());
		}
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

	/*auto collider = m_pPlayers[0]->GetCharacter()->GetComponent<ColliderComponent>()->GetCollider();
	auto gridPos = GetCellData(m_pPlayers[0]->GetCharacter()->GetPosition());
	if (m_pBlocks[gridPos.first][gridPos.second]->CheckIfColliding(collider))
	{
		m_pBlocks[gridPos.first][gridPos.second]->Destroy();
		m_Grid[gridPos.first][gridPos.second] = false;
	}*/
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
	std::shared_ptr<Character> player1;
	std::shared_ptr<Character> player2;
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

				player1 = std::make_shared<Character>(m_P1Name, m_P1File, 4, 4);
				player1->Init();
				player1->SetPosition(m_Player1StartPos);
				m_pPlayers.push_back(player1);
				break;
			case CellDefinition::Player2:
				DestroyCell(i, j);
				pos = GetCellPosition(i, j);
				pos.x += 16;
				pos.y += 16;
				m_Player2StartPos = pos;

				player2 = std::make_shared<Character>(m_P2Name, m_P2File, 4, 4);
				player2->Init();
				player2->SetPosition(m_Player2StartPos);
				m_pPlayers.push_back(player1);
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

void dae::GridSystem::AddGridToScene()
{
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Columns; j++)
		{
			AddToScene(m_pBlocks[i][j]->GetBlock());
		}
	}
	for (std::shared_ptr<Character> element : m_pEnemies)
	{
		AddToScene(element->GetCharacter());
	}

	for (std::shared_ptr<Character> element : m_pPlayers)
	{
		AddToScene(element->GetCharacter());
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