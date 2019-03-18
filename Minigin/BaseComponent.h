#pragma once

namespace dae {
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;

	private:
		std::string mName{};
	};
}
