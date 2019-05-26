#pragma once
#include "Scene.h"

namespace dae {
	class GameObject;
	class GridSystem;
	class Character;
	class LevelScene : public Scene
	{
	public:
		LevelScene(const std::string& name);
		void Init();

		void Update() override;
		void Render() const override;

		void InitPlayer1Controles(std::shared_ptr<Character> gameObject);

	private:
		std::shared_ptr<GridSystem> m_pTheGrid;
		std::shared_ptr<GameObject> m_Score;
	};
}
