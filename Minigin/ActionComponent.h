#pragma once
#include "BaseComponent.h"

namespace dae {
	class ActionComponent :public BaseComponent
	{
	public:
		ActionComponent();
		~ActionComponent() = default;

		void DoAction();

		void Update() override {}
	};
}
