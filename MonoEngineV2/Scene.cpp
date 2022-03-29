#include "pch.h"
#include "Scene.h"

Scene::Scene(_In_ const std::string& name)
	: m_name(name)
{ }

Scene::~Scene()
{
	for (GameObject* obj : m_objects)
		delete obj;
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::Update()
{
	for (GameObject* obj : m_objects)
		obj->Update();
}

void Scene::Render()
{
	for (GameObject* obj : m_objects)
		obj->Render();
}

_Success_(return != nullptr) _Check_return_
GameObject* Scene::CreateObject(_In_ const std::string& name)
{
	GameObject* obj = new GameObject(name);
	obj->m_scene = this;
	m_objects.push_back(obj);
	return obj;
}

void Scene::DestroyObject(_In_opt_ GameObject* obj)
{
	if (obj == nullptr)
		return;

	for (auto it = m_objects.cbegin(); it != m_objects.cend(); it++)
		if (*it == obj)
		{
			m_objects.erase(it);
			obj->m_scene = nullptr;
			delete obj;
			return;
		}
}

GameObject* Scene::FindObjectByName(const std::string& name) const
{
	for (GameObject* obj : m_objects)
		if (obj->GetName() == name)
			return obj;
}
