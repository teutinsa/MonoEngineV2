#include "pch.h"
#include "SceneManager.h"

#include "ILRuntime.h"

SceneManager::SceneManager()
	: m_currentScene(nullptr), m_sceneDefs(nullptr)
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

void SceneManager::DestroyScene(_In_ Scene* scene)
{
	if (scene == nullptr)
		return;

	for(auto it = m_scenes.cbegin(); it != m_scenes.cend(); it++)
		if (*it == scene)
		{
			m_scenes.erase(it);
			SafeDel(scene);
			return;
		}
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

void SceneManager::SetSceneDefs(_In_ const std::vector<ObjectHandle>* sceneDefs)
{
	m_sceneDefs = sceneDefs;
}

void SceneManager::LoadScene(_In_ int index)
{
	if (m_sceneDefs == nullptr)
		return;

	MonoDelegate* sceneDefDel = (MonoDelegate*)m_sceneDefs->at(index).GetObject();

	Scene* scene = CreateScene("Scene");

	void* args[1];
	args[0] = scene->GetManagedObject();

	ThrowOnExc(ILRuntime::GetCurrent()->Invoke(sceneDefDel, args, nullptr));

	DestroyScene(m_currentScene);
	m_currentScene = scene;
}

void SceneManager::RegisterIntCalls()
{
	Scene::RegisterIntCalls();
}

SceneManager* SceneManager::s_current;