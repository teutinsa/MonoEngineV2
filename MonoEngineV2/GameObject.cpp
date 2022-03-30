#include "pch.h"
#include "GameObject.h"

#include "ILRuntime.h"

GameObject::GameObject(_In_ const std::string& name)
	: m_name(name), m_scene(nullptr)
{
	static MonoClass* gameObjectCl;
	if (gameObjectCl == nullptr)
		gameObjectCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "GameObject");
	
	m_managed = ILRuntime::GetCurrent()->New(gameObjectCl);
	m_handle = mono_gchandle_new(m_managed, false);

	static MonoClass* objectCl;
	if (objectCl == nullptr)
		objectCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object");
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(objectCl, "m_native");

	void* ptr = this;
	mono_field_set_value(m_managed, nativeFld, &ptr);
}

GameObject::~GameObject()
{
	mono_gchandle_free(m_handle);
}

void GameObject::Update()
{
	for (Component* comp : m_components)
		comp->Update();
}

void GameObject::Render()
{
	for (Component* comp : m_components)
		comp->Render();
}

_Ret_
Scene* GameObject::GetScene() const
{
	return m_scene;
}

std::string GameObject::GetName() const
{
	return m_name;
}

void GameObject::RemoveComonent(_In_opt_ const Component* comp)
{
	for (auto it = m_components.cbegin(); it != m_components.cend(); it++)
		if (*it == comp)
		{
			m_components.erase(it);
			delete comp;
			return;
		}
}

void GameObject::RegisterIntCalls()
{
	Component::RegisterIntCalls();
}

void GameObject::AddComponent(_In_ Component* comp)
{
	if (comp->m_gameObject != nullptr)
		throw std::runtime_error("The component is already used by another game object.");

	comp->m_gameObject = this;
	m_components.push_back(comp);
}

_Success_(return != nullptr) _Check_return_ _Ret_maybenull_
Component* GameObject::GetComponent(_In_ size_t hash_code) const
{
	for (Component* comp : m_components)
		if (comp->GetHash() == hash_code)
			return comp;
	return nullptr;
}

std::vector<Component*> GameObject::GetComponents(_In_ size_t hash_code) const
{
	std::vector<Component*> tmp;

	for (Component* comp : m_components)
		if (comp->GetHash() == hash_code)
			tmp.push_back(comp);

	return tmp;
}
