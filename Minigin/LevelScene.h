#pragma once
#include "Scene.h"

namespace dae {
	class GameObject;
	class GridSystem;
	class Character;
	class LevelScene final : public Scene, public std::enable_shared_from_this<LevelScene>
	{
	public:
		LevelScene(const std::string& name);
		~LevelScene();
		void Init();

		void Update() override;
		void Render() const override;

		void InitPlayer1Controles(std::shared_ptr<Character> gameObject);

		void Reset();

	private:
		std::shared_ptr<GridSystem> m_pTheGrid;
		std::shared_ptr<GameObject> m_Score;
	};
}
