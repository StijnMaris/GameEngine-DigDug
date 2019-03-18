#pragma once

namespace dae {
	class BaseComponent
	{
	public:
		BaseComponent(std::string name);
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;

	private:
		std::string m_Name{};
	};
}
