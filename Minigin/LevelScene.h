#pragma once
#include "Scene.h"

namespace dae {
	class GameObject;
	class GridSystem;
	class LevelScene : public Scene
	{
	public:
		LevelScene(const std::string& name);
		void Init();

		void Update() override;
		void Render() const override;

		void InitPlayer1Controles(std::shared_ptr<GameObject> gameObject);

	private:
		std::shared_ptr<GridSystem> m_pTheGrid;
	};
}
