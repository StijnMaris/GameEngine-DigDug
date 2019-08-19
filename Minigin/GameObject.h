#pragma once
#include <memory>

#include "Transform.h"
#include <glm/vec2.hpp>

namespace dae
{
	class BaseComponent;
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void AddComponent(const std::shared_ptr<BaseComponent> component);

		template <class T>
		//std::is_base_of<dae::BaseComponent, T>
		std::shared_ptr<T> GetComponent()const;

		void Init();
		void Update();
		void Render() const;

		glm::vec3 GetPosition() const;
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(glm::vec3 pos = { 0,0,0 });

		const glm::vec3& GetScale() const;
		void SetScale(float x, float y, float z = 0);
		void SetScale(glm::vec3 scale = { 1,1,1 });

		GameObject(const std::string& name);
		~GameObject();
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
