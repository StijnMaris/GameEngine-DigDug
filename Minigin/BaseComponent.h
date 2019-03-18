#pragma once

namespace dae {
	class BaseComponent
	{
	public:
		virtual BaseComponent() = 0;
		~BaseComponent();

		virtual void Update() = 0;

	private:
		std::string mName{};
	};
}
