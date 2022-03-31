#include "pch.h"
#include "ILRuntime.h"

ILRuntime::ILRuntime(_In_ const std::string& path, _In_ const std::string& appName)
	: m_coreLib(nullptr), m_engineLib(nullptr), m_userLib(nullptr)
{
	s_current = this;

	mono_set_dirs(path.c_str(), path.c_str());
	mono_config_parse(nullptr);
	m_domain = mono_jit_init(appName.c_str());
}

ILRuntime::~ILRuntime()
{
	mono_jit_cleanup(m_domain);
}

_Success_(return != nullptr)
void ILRuntime::RegIntCall(const std::string & name, void* func)
{
	mono_add_internal_call(name.c_str(), func);
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

_Success_(return != nullptr) _Check_return_
MonoClass* ILRuntime::GetCoreClasByName(_In_ const std::string& names_space, _In_ const std::string& name) const
{
	return mono_class_from_name(m_coreLib, names_space.c_str(), name.c_str());
}

_Success_(return != nullptr) _Check_return_
MonoClass* ILRuntime::GetLibClasByName(_In_ const std::string& names_space, _In_ const std::string& name) const
{
	return mono_class_from_name(m_engineLib, names_space.c_str(), name.c_str());
}

_Success_(return != nullptr) _Check_return_
MonoClass* ILRuntime::GetUserClasByName(_In_ const std::string& names_space, _In_ const std::string& name) const
{
	return mono_class_from_name(m_userLib, names_space.c_str(), name.c_str());
}

_Success_(return != nullptr) _Check_return_
MonoObject* ILRuntime::New(_In_ MonoClass* klass)
{
	return mono_object_new(m_domain, klass);
}

_Success_(return != nullptr) _Check_return_
MonoException* ILRuntime::Invoke(_In_ MonoMethod* method, _In_opt_ MonoObject* obj, _In_opt_ void** args, _Outptr_opt_result_maybenull_ MonoObject** ret)
{
	MonoObject* exc = nullptr;

	MonoMethod* mth = method;
	if (obj != nullptr)
		mth = mono_object_get_virtual_method(obj, method);

	if(ret == nullptr)
		mono_runtime_invoke(method, obj, args, &exc);
	else
		(*ret) = mono_runtime_invoke(method, obj, args, &exc);

	return (MonoException*)exc;
}

_Success_(return != nullptr) _Check_return_
MonoException* ILRuntime::Invoke(_In_ MonoDelegate* delegat, _In_opt_ void** args, _Outptr_opt_result_maybenull_ MonoObject** ret)
{
	MonoObject* exc = nullptr;

	if(ret == nullptr)
		mono_runtime_delegate_invoke((MonoObject*)delegat, args, &exc);
	else
		(*ret) = mono_runtime_delegate_invoke((MonoObject*)delegat, args, &exc);

	return (MonoException*)exc;
}

ILRuntime* ILRuntime::s_current;