#pragma once
namespace dae {
	class GameObject;
	class LevelScene
	{
	public:
		LevelScene();

		void Init();

		void InitPlayer1Controles(std::shared_ptr<GameObject> gameObject);
	};
}
