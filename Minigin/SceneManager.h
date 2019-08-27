#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);
		std::shared_ptr<Scene> CreateScene(std::shared_ptr<Scene> scene);
		//Scene & GetScene(const std::string& name);

		void Update();
		void Render();

		void SetActiveScene(const std::string& name);
		void DisableScene(const std::string& name);
		bool IsSceneActive(const std::string& name);

		void Reset()
		{
			m_pScenes.clear();
			m_pActiveScenes.clear();
		}

		std::shared_ptr<Scene>GetActiveScene()
		{
			return m_pActiveScenes.at(0);
		}

	private:
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::vector<std::shared_ptr<Scene>> m_pActiveScenes;
	};
}
