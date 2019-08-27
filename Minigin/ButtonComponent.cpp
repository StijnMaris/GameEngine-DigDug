#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "SceneManager.h"
#include "LevelScene.h"
#include "InputManager.h"

dae::ButtonComponent::ButtonComponent(
	glm::vec3 normalColor,
	glm::vec3 highlightColor,
	glm::vec3 pressedColor) :BaseComponent("ButtonComponent"),
	m_NormalColor(normalColor),
	m_HighlightColor(highlightColor),
	m_PressedColor(pressedColor)

{
}

void dae::ButtonComponent::Update()
{
}

void dae::ButtonComponent::OnClick(std::string levelName)
{
	auto&sceneMan = SceneManager::GetInstance();
	sceneMan.SetActiveScene(levelName);
	std::dynamic_pointer_cast<LevelScene>(sceneMan.GetActiveScene())->Init();
}