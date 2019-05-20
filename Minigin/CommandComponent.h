#pragma once
#include "BaseComponent.h"
#include <queue>
#include "Command.h"

namespace dae
{
	class CommandComponent final : public dae::BaseComponent
	{
	public:
		CommandComponent();
		virtual ~CommandComponent() = default;

		void Update() override;

		void AddCommand(std::shared_ptr<Command> pCommand);

	private:
		std::queue<std::shared_ptr<Command>>m_Commands;
	};
}
