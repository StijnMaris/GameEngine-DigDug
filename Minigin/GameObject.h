#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"

namespace dae
{
	class BaseComponent;
	class GameObject
	{
	public:
		void AddComponent(const std::shared_ptr<BaseComponent>& component);

		template <class T>
		std::shared_ptr<std::is_base_of<BaseComponent, T>>& GetComponent();

		void Update();
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject(const std::string& name);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		std::string m_Name{};
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;
		std::vector < std::shared_ptr<BaseComponent>> m_pComponents{};
	};
}
