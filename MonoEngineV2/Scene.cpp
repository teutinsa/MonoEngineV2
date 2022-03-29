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
