#include "pch.h"
#include "GameObject.h"

#include "ILRuntime.h"

GameObject::GameObject(_In_ const std::string& name)
	: m_name(name), m_scene(nullptr), m_active(true)
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

	transform = new Transform(this);
}

GameObject::~GameObject()
{
	SafeDel(transform);

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

MonoObject* GameObject::GetManagedObject() const
{
	return m_managed;
}

void GameObject::RegisterIntCalls()
{
	ILRuntime::RegIntCall("MonoEngineV2Lib.GameObject::GetComponent", Mono_GetComponent);
	ILRuntime::RegIntCall("MonoEngineV2Lib.GameObject::AddComponent", Mono_AddComponent);
	ILRuntime::RegIntCall("MonoEngineV2Lib.GameObject::RemoveComponent", Mono_RemoveComponent);

	Transform::RegisterIntCalls();
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

MonoString* GameObject::Mono_get_Name(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	return mono_string_new_wrapper(go->m_name.c_str());
}

void GameObject::Mono_set_Name(MonoObject* obj, MonoString* value)
{
	if (value == nullptr)
		return;

	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	go->m_name = mono_string_to_utf8(value);
}

bool GameObject::Mono_get_Active(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	return go->m_active;
}

void GameObject::Mono_set_Active(MonoObject* obj, bool value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	go->m_active = value;
}

MonoObject* GameObject::Mono_get_Transform(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	return go->transform->GetManaged();
}

MonoObject* GameObject::Mono_GetComponent(MonoObject* obj, MonoReflectionType* type)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	MonoClass* typeCl = mono_type_get_class(mono_reflection_type_get_type(type));
	for (Component* comp : go->m_components)
		if (mono_object_get_class(comp->m_managed) == typeCl)
			return comp->m_managed;

	return nullptr;
}

MonoObject* GameObject::Mono_AddComponent(MonoObject* obj, MonoReflectionType* type)
{
	if (type == nullptr)
		return nullptr;

	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	MonoType* typeTy = mono_reflection_type_get_type(type);
	MonoClass* typeCl = mono_type_get_class(typeTy);
	MonoObject* compObj = nullptr;

	if (typeCl == nullptr)
		return nullptr;
	
	static MonoClass* scriptCl;
	if(scriptCl == nullptr)
		scriptCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Script");

	switch ((int)typeCl)
	{
	default:
	{
		if (mono_class_get_parent(typeCl) == scriptCl)
		{
			ScriptComponent* comp = new ScriptComponent(typeCl);
			go->AddComponent(comp);
			compObj = comp->GetManagedObject();
		}
		break;
	}
	}

	return compObj;
}

void GameObject::Mono_RemoveComponent(MonoObject* obj, MonoObject* compObj)
{
	if (compObj == nullptr)
		return;

	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	GameObject* go = nullptr;
	mono_field_get_value(obj, nativeFld, &go);

	Component* comp = nullptr;
	mono_field_get_value(compObj, nativeFld, &comp);

	go->RemoveComonent(comp);
}
