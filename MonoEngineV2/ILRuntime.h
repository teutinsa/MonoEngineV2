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

private:
	static ILRuntime* s_current;
	MonoDomain* m_domain;
	MonoImage* m_coreLib;
	MonoImage* m_engineLib;
	MonoImage* m_userLib;
};