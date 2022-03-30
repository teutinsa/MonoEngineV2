#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: m_currentScene(nullptr)
{ }

SceneManager::~SceneManager()
{
	for (Scene* ptr : m_scenes)
		delete ptr;
	m_scenes.clear();
}

_Success_(return != nullptr)
SceneManager* SceneManager::GetCurrent()
{
	return s_current;
}

_Ret_maybenull_
Scene* SceneManager::GetCurrentScene() const
{
	return m_currentScene;
}

_Success_(return != nullptr) _Check_return_
Scene* SceneManager::CreateScene(_In_ const std::string& name)
{
	if (SceneWithNameExists(name))
		return nullptr;
	Scene* s = new Scene(name);
	m_scenes.push_back(s);
	return s;
}

bool SceneManager::SceneWithNameExists(_In_ const std::string& name) const
{
	for (const Scene* s : m_scenes)
		if (s->GetName() == name)
			return true;
	return false;
}

_Success_(return != nullptr) _Check_return_
Scene* SceneManager::GetSceneByName(_In_ const std::string& name) const
{
	for (Scene* s : m_scenes)
		if (s->GetName() == name)
			return s;
	return nullptr;
}

void SceneManager::SetCurrentScene(_In_ Scene* scene)
{
	m_currentScene = scene;
}

void SceneManager::Update()
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}

void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}

SceneManager* SceneManager::s_current;