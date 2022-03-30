#include "pch.h"
#include "Resource.h"

#include "ILRuntime.h"

Resource::Resource(MonoClass* klass)
	: m_class(klass)
{
	m_managed = ILRuntime::GetCurrent()->New(m_class);
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

Resource::~Resource()
{
	mono_gchandle_free(m_handle);
}

MonoObject* Resource::GetManagedObject() const
{
	return m_managed;
}
