#include "MiniginPCH.h"
#include "AStar.h"
#include "GridSystem.h"

dae::AStar::AStar(std::shared_ptr<GridSystem> gridSys) : m_pGridSystem(gridSys)
{
}

dae::AStar::~AStar()
{
}

std::vector<std::pair<int, int>> dae::AStar::FindPath(glm::vec3 curPos, glm::vec3 targetPos)
{
	std::pair<int, int> m_TargetCellData = m_pGridSystem->GetCellData(targetPos);

	Node* pCurrent = nullptr;
	std::vector<Node*> openSet, closedSet;
	openSet.push_back(new Node(m_pGridSystem->GetCellData(curPos)));

	while (!openSet.empty())
	{
		pCurrent = *openSet.begin();
		for (auto pNode : openSet)
		{
			if (pNode->GetScore() <= pCurrent->GetScore())
			{
				pCurrent = pNode;
			}
		}

		if (pCurrent->m_NodeData == m_TargetCellData)
		{
			break;
		}

		closedSet.push_back(pCurrent);
		openSet.erase(std::find(openSet.begin(), openSet.end(), pCurrent));

		for (unsigned int i = 0; i < m_Directions.size(); i++)
		{
			std::pair<int, int> newCoordinates = std::make_pair(pCurrent->m_NodeData.first + m_Directions[i].first, pCurrent->m_NodeData.second + m_Directions[i].second);
			if (m_pGridSystem->GetCellState(newCoordinates) || FindNodeInList(closedSet, newCoordinates) != nullptr)
			{
				continue;
			}

			unsigned int totalCost = pCurrent->G + ((i < 4) ? 10 : 14);

			Node* successor = FindNodeInList(openSet, newCoordinates);
			if (successor == nullptr)
			{
				successor = new Node(newCoordinates, pCurrent);
				successor->G = totalCost;
				successor->H = ManhattenHeuristic(successor->m_NodeData, m_TargetCellData);
				openSet.push_back(successor);
			}
			else if (totalCost < successor->G)
			{
				successor->m_pParent = pCurrent;
				successor->G = totalCost;
			}
		}
	}

	std::vector<std::pair<int, int>> m_pPath;
	while (pCurrent != nullptr)
	{
		m_pPath.push_back(pCurrent->m_NodeData);
		pCurrent = pCurrent->m_pParent;
	}
	std::reverse(m_pPath.begin(), m_pPath.end());

	for (int i = 0; i < (int)openSet.size(); i++)
	{
		delete openSet[i];
		openSet[i] = nullptr;
	}
	openSet.clear();
	for (int i = 0; i < (int)closedSet.size(); i++)
	{
		delete closedSet[i];
		closedSet[i] = nullptr;
	}
	closedSet.clear();
	return m_pPath;
}