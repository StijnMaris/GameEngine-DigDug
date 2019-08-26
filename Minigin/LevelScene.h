#pragma once
#include "Scene.h"

namespace dae {
	class GameObject;
	class GridSystem;
	class Character;
	//class Observer;
	class LevelScene final : public Scene, public std::enable_shared_from_this<LevelScene>
	{
	public:
		LevelScene(const std::string& name, const std::string& LevelFile);
		~LevelScene();
		void Init();

		void Update() override;
		void Render() const override;

		void InitPlayer1Controles(std::shared_ptr<Character> gameObject);

		void Reset();

		std::shared_ptr<GridSystem> GetGridSystem()const
		{
			return  m_pTheGrid;
		}

	private:
		std::shared_ptr<GridSystem> m_pTheGrid;
		std::shared_ptr<GameObject> m_Score;
		//std::shared_ptr<dae::Score> m_ScoreObserver;
		std::string m_FilePath;
	};
}
