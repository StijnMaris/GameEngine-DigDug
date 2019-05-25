#pragma once
#include "Scene.h"

namespace dae {
	class GameObject;
	class LevelScene : public Scene
	{
	public:
		LevelScene(const std::string& name);
		void Init();

		void Update() override;
		void Render() const override;

		void InitPlayer1Controles(std::shared_ptr<GameObject> gameObject);

	private:
	};
}
