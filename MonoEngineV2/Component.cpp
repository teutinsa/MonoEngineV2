#include "pch.h"
#include "Component.h"

#include "ILRuntime.h"

Component::Component(_In_ MonoClass* klass)
{
	m_managed = ILRuntime::GetCurrent()->New(klass);
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

Component::~Component()
{
	mono_gchandle_free(m_handle);
}

void Component::Update()
{
}

void Component::Render()
{
}

void Component::RegisterIntCalls()
{
	ScriptComponent::RegisterIntCalls();
}

_Ret_notnull_
MonoObject* Component::GetManagedObject() const
{
	return m_managed;
}

ScriptComponent::ScriptComponent(_In_ MonoClass* klass)
	: m_class(klass), Component(klass), m_firstUpdate(true)
{
	m_onCreateMethod = mono_class_get_method_from_name(klass, "OnCreate", 0);
	m_onDestroyMethod = mono_class_get_method_from_name(klass, "OnDestroy", 0);
	m_onStartMethod = mono_class_get_method_from_name(klass, "OnStart", 0);
	m_onUpdateMethod = mono_class_get_method_from_name(klass, "OnUpdate", 0);

	InvokeOnCreate();
}

ScriptComponent::~ScriptComponent()
{
	InvokeOnDestroy();
	Component::~Component();
}

size_t ScriptComponent::MakeHash(_In_ MonoClass* klass)
{
	return typeid(ScriptComponent).hash_code();
}

void ScriptComponent::Update()
{
	if (m_firstUpdate)
	{
		InvokeOnStart();
		m_firstUpdate = false;
	}
	InvokeOnUpdate();
}

size_t ScriptComponent::GetHash() const
{
	return MakeHash(m_class);
}

_Ret_notnull_
MonoType* ScriptComponent::GetType() const
{
	return mono_class_get_type(m_class);
}

void ScriptComponent::RegisterIntCalls()
{
}

void ScriptComponent::InvokeOnCreate()
{
	if (m_onCreateMethod != nullptr)
		ThrowOnExc(ILRuntime::GetCurrent()->Invoke(m_onCreateMethod, GetManagedObject(), nullptr, nullptr));
}

void ScriptComponent::InvokeOnDestroy()
{
	if (m_onDestroyMethod != nullptr)
		ThrowOnExc(ILRuntime::GetCurrent()->Invoke(m_onDestroyMethod, GetManagedObject(), nullptr, nullptr));
}

void ScriptComponent::InvokeOnStart()
{
	if (m_onStartMethod != nullptr)
		ThrowOnExc(ILRuntime::GetCurrent()->Invoke(m_onStartMethod, GetManagedObject(), nullptr, nullptr));
}

void ScriptComponent::InvokeOnUpdate()
{
	if (m_onUpdateMethod != nullptr)
		ThrowOnExc(ILRuntime::GetCurrent()->Invoke(m_onUpdateMethod, GetManagedObject(), nullptr, nullptr));
}
