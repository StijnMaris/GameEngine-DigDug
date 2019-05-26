#pragma once
#include "Singleton.h"
#include <glm/vec3.hpp>

namespace dae
{
	class GridSystem;
	struct Node
	{
	public:
		Node(std::pair<int, int> nodeData, Node* parent = nullptr)
			: m_NodeData(nodeData), m_pParent(parent)
		{
			G = H = 0;
		}
		unsigned int GetScore()
		{
			return G + H;
		}

		unsigned int G, H;
		std::pair<int, int> m_NodeData;
		Node* m_pParent;
	private:
	};

	class AStar final : public dae::Singleton<AStar>
	{
	public:
		AStar(std::shared_ptr<GridSystem> gridSys);
		virtual ~AStar();

		std::vector<std::pair<int, int>> FindPath(glm::vec3 curPos, glm::vec3 targetPos);

		std::pair<int, int> GetDelta(std::pair<int, int> current, std::pair<int, int> target)
		{
			return { std::make_pair(current.first - target.first, current.second - target.second) };
		}

		int ManhattenHeuristic(std::pair<int, int> current, std::pair<int, int> target)
		{
			auto delta = GetDelta(current, target);
			return 	static_cast<int>(10 * std::sqrt(std::pow(delta.first, 2) + std::pow(delta.second, 2)));
		}

		Node* FindNodeInList(std::vector<Node*> nodeList, std::pair<int, int> coords)
		{
			for (int i = 0; i < (int)nodeList.size(); i++)
			{
				if (nodeList[i]->m_NodeData == coords)
				{
					return nodeList[i];
				}
			}
			return nullptr;
		}

	private:
		std::shared_ptr<GridSystem> m_pGridSystem;

		std::vector<std::pair<int, int>> m_Directions = { {1,0}, {-1, 0}, {0,1}, {0,-1} };
	};
}