#pragma once
#include "Core.h"

#include "Resource.h"

class ResourceManager
{
	friend class ResourceLoader2D;
	friend class ResourceLoader3D;

public:
	ResourceManager();
	~ResourceManager();

	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
	/// <summary>
	/// Tries to get a resource with a specific name.
	/// </summary>
	/// <param name="name">The name to search for.</param>
	/// <returns>A pointer to a resource, null if no resource with the given name was found.</returns>
	_Success_(return != nullptr) _Check_return_ _Ret_maybenull_ Resource* GetResource(_In_ const std::string& name) const;
	/// <summary>
	/// Gets the managed counter part of this object.
	/// </summary>
	_Ret_notnull_ MonoObject* GetManagedObject() const;

private:
	std::unordered_map<std::string, Resource*> m_resources;
	MonoObject* m_managed;
	uint32_t m_handle;

	/// <summary>
	/// Adds a resource to the manager.
	/// </summary>
	/// <param name="name">The name of the resources.</param>
	/// <param name="rsc">The resource to add.</param>
	void AddResource(_In_ const std::string& name, _In_ Resource* rsc);
};