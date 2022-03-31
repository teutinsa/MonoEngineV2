#include "pch.h"
#include "ResourceManager.h"

#include "ResourceLoader2D.h"
#include "ILRuntime.h"

ResourceManager::ResourceManager()
{
	static MonoClass* rscMngrCl;
	if (rscMngrCl == nullptr)
		rscMngrCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "ResourceManager");

	m_managed = ILRuntime::GetCurrent()->New(rscMngrCl);
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

ResourceManager::~ResourceManager()
{
    for (auto& kv : m_resources)
        delete kv.second;
    m_resources.clear();

	mono_gchandle_free(m_handle);
}

void ResourceManager::RegisterIntCalls()
{
    ResourceLoader2D::RegisterIntCalls();
}

_Success_(return != nullptr) _Check_return_ _Ret_maybenull_
Resource* ResourceManager::GetResource(_In_ const std::string& name) const
{
    if (!m_resources.contains(name))
        return nullptr;

	return m_resources.at(name);
}

_Ret_notnull_
MonoObject* ResourceManager::GetManagedObject() const
{
    return m_managed;
}

void ResourceManager::AddResource(_In_ const std::string& name, _In_ Resource* rsc)
{
	if (m_resources.contains(name))
		throw std::runtime_error("Resource with name already exists!");

	m_resources[name] = rsc;
}
