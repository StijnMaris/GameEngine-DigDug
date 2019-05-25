#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const std::string& name);
		void AddGameObject(const std::shared_ptr<GameObject>& gameObject);

		virtual void Update();
		virtual void Render() const;

		const std::string& GetSceneName() const
		{
			return m_Name;
		}

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:

		std::string m_Name{};
		std::vector < std::shared_ptr<GameObject>> m_pGameObjects{};

		static unsigned int idCounter;
	};
}
