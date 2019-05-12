#pragma once
#include "BaseComponent.h"

namespace  dae {
	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent();
		~MovementComponent();

		void Update() override;
	};
}
