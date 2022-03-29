#include "pch.h"
#include "ILRuntime.h"

ILRuntime::ILRuntime(_In_ const std::string& path, _In_ const std::string& appName)
	: m_coreLib(nullptr), m_engineLib(nullptr), m_userLib(nullptr)
{
	mono_set_dirs(path.c_str(), path.c_str());
	mono_config_parse(nullptr);
	m_domain = mono_jit_init(appName.c_str());
}

ILRuntime::~ILRuntime()
{
	mono_jit_cleanup(m_domain);
}

ILRuntime* ILRuntime::GetCurrent()
{
	return s_current;
}

void ILRuntime::LoadCoreLib()
{
	m_coreLib = mono_get_corlib();
}

void ILRuntime::LoadEngineLib(_In_ const std::string& filename)
{
	if (m_engineLib != nullptr)
		return;

	m_engineLib = mono_assembly_get_image(mono_domain_assembly_open(m_domain, filename.c_str()));
}

void ILRuntime::LoadUserLib(_In_ const std::string& filename)
{
	if (m_userLib != nullptr)
		return;

	m_userLib = mono_assembly_get_image(mono_domain_assembly_open(m_domain, filename.c_str()));
}

void ILRuntime::GC()
{
	mono_gc_collect(mono_gc_max_generation());
}

int64_t ILRuntime::GetHeapSize() const
{
	return mono_gc_get_heap_size();
}

int64_t ILRuntime::GetHeapUsed() const
{
	return mono_gc_get_used_size();
}

_Success_(return != nullptr) _Check_return_
MonoMethod* ILRuntime::FetchUserEntryPoint() const
{
	if(m_userLib == nullptr)
		return nullptr;

	MonoMethodDesc* desc = mono_method_desc_new("*:Main()", false);
	MonoMethod* mth = mono_method_desc_search_in_image(desc, m_userLib);
	mono_method_desc_free(desc);

	MonoMethodSignature* sig = mono_method_signature(mth);
	MonoClass* retClass = mono_type_get_class(mono_signature_get_return_type(sig));
	MonoClass* dataClass = mono_class_from_name(m_engineLib, "MonoEngineV2Lib", "StartupData");

	if (retClass != dataClass)
		return nullptr;

	return mth;
}

ILRuntime* ILRuntime::s_current;