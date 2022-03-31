#pragma once
#include "Core.h"

class ILRuntime
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="path">A path to the runtime directory.</param>
	/// <param name="appName">The application name to be passed to the managed domain.</param>
	ILRuntime(_In_ const std::string& path, _In_ const std::string& appName);
	~ILRuntime();

	/// <summary>
	/// Registers a internal call in the runtime.
	/// </summary>
	/// <param name="name">The full name of the internal call method.</param>
	/// <param name="func">The unmanaged function pointer for the internal call to use.</param>
	static void RegIntCall(const std::string& name, void* func);
	/// <summary>
	/// Gets the current ILRuntime instance.
	/// </summary>
	/// <returns>A pointer to the current ILRuntime instance.</returns>
	_Success_(return != nullptr) static ILRuntime* GetCurrent();
	/// <summary>
	/// Loads the core library. (mscorlib.dll)
	/// </summary>
	void LoadCoreLib();
	/// <summary>
	/// Loads the mono engine library.
	/// </summary>
	/// <param name="filename">The file name to the engine library.</param>
	void LoadEngineLib(_In_ const std::string& filename);
	/// <summary>
	/// Loads the mono user library.
	/// </summary>
	/// <param name="filename">The file name to the user library.</param>
	void LoadUserLib(_In_ const std::string& filename);
	/// <summary>
	/// Invokes a garbage collection cycle.
	/// </summary>
	void GC();
	/// <summary>
	/// Gets the size of the managed heap in bytes.
	/// </summary>
	int64_t GetHeapSize() const;
	/// <summary>
	/// Gets the number of bytes used in the managed heap.
	/// </summary>
	int64_t GetHeapUsed() const;
	/// <summary>
	/// Tries to get the user defined entry point from the user assembly.
	/// </summary>
	/// <returns>A mono pointer to the user defined entry point, null if no entry point was found.</returns>
	_Success_(return != nullptr) _Check_return_ MonoMethod* FetchUserEntryPoint() const;
	/// <summary>
	/// Gets a class by name from the core library.
	/// </summary>
	/// <param name="names_space">The namespace of the class.</param>
	/// <param name="name">The name of the class.</param>
	/// <returns>A mono pointer to the found class.</returns>
	_Success_(return != nullptr) _Check_return_ MonoClass* GetCoreClasByName(_In_ const std::string& names_space, _In_ const std::string& name) const;
	/// <summary>
	/// Gets a class by name from the engine library.
	/// </summary>
	/// <param name="names_space">The namespace of the class.</param>
	/// <param name="name">The name of the class.</param>
	/// <returns>A mono pointer to the found class.</returns>
	_Success_(return != nullptr) _Check_return_ MonoClass* GetLibClasByName(_In_ const std::string& names_space, _In_ const std::string& name) const;
	/// <summary>
	/// Gets a class by name from the user library.
	/// </summary>
	/// <param name="names_space">The namespace of the class.</param>
	/// <param name="name">The name of the class.</param>
	/// <returns>A mono pointer to the found class.</returns>
	_Success_(return != nullptr) _Check_return_ MonoClass* GetUserClasByName(_In_ const std::string& names_space, _In_ const std::string& name) const;
	/// <summary>
	/// Instantiates a new managed object.
	/// </summary>
	/// <param name="klass">The class of the object.</param>
	/// <returns>A mono pointer referencing the managed object.</returns>
	_Success_(return != nullptr) _Check_return_ MonoObject* New(_In_ MonoClass* klass);
	/// <summary>
	/// Invokes a given method, with the provided arguments.
	/// </summary>
	/// <param name="method">The method to invoke.</param>
	/// <param name="obj">The instance object to call the method on, null if static method.</param>
	/// <param name="args">The arguments.</param>
	/// <param name="ret">A pointer to a possible return object.</param>
	/// <returns>A mono pointer to possible managed exception, null if none was thrown.</returns>
	_Success_(return != nullptr) _Check_return_ MonoException* Invoke(_In_ MonoMethod* method, _In_opt_ MonoObject* obj, _In_opt_ void** args, _Outptr_opt_result_maybenull_ MonoObject** ret);
	/// <summary>
	/// Invokes a given delegate, with the provided arguments.
	/// </summary>
	/// <param name="delegat">The delegate to invoke.</param>
	/// <param name="args">The arguments.</param>
	/// <param name="ret">A pointer to a possible return object.</param>
	/// <returns>A mono pointer to possible managed exception, null if none was thrown.</returns>
	_Success_(return != nullptr) _Check_return_ MonoException* Invoke(_In_ MonoDelegate* delegat, _In_opt_ void** args, _Outptr_opt_result_maybenull_ MonoObject** ret);

private:
	static ILRuntime* s_current;
	MonoDomain* m_domain;
	MonoImage* m_coreLib;
	MonoImage* m_engineLib;
	MonoImage* m_userLib;
};