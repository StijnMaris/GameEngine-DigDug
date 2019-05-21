#pragma once

namespace dae {
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(std::string name);
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;
		std::shared_ptr<GameObject> GetOwner() const;
		void SetOwner(std::shared_ptr<GameObject> owner);
	private:
		std::string m_Name{};
		std::shared_ptr<GameObject> m_pOwner;
	};
}
