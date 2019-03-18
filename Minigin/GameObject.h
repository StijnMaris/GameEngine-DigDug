#pragma once
#include <memory>

#include "Transform.h"

namespace dae
{
	class BaseComponent;
	class GameObject final
	{
	public:
		void AddComponent(const std::shared_ptr<BaseComponent>& component);

		template <class T>
		//std::is_base_of<dae::BaseComponent, T>
		std::shared_ptr<T> GetComponent()const;

		void Update();
		void Render() const;

		void SetPosition(float x, float y);

		GameObject(const std::string& name);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool HasRenderComponent()const;

		std::string m_Name{};
		std::vector < std::shared_ptr<BaseComponent>> m_pComponents{};
	};
}
