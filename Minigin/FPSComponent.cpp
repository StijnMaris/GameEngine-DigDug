#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<TextComponent> textComponent) :BaseComponent("FPS"), m_pTextComponent(textComponent)
{
}

void dae::FPSComponent::Update()
{
	m_pTextComponent->SetText(std::to_string(Time::GetInstance().GetFps()));
}