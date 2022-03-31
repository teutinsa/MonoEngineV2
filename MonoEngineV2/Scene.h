#pragma once

#include "GameObject.h"
#include "ColorF.h"
#include "ResourceManager.h"

class Scene
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="name">The name of the scene.</param>
	Scene(_In_ const std::string& name);
	~Scene();

	/// <summary>
	/// Gets the name of the game object.
	/// </summary>
	std::string GetName() const;
	/// <summary>
	/// Update
	/// </summary>
	void Update();
	/// <summary>
	/// Render
	/// </summary>
	void Render();
	/// <summary>
	/// Creates a new game object with the given name.
	/// </summary>
	/// <param name="name">The name of the new game object.</param>
	/// <returns>A pointer to the new game object.</returns>
	_Success_(return != nullptr) _Check_return_ GameObject* CreateObject(_In_ const std::string& name);
	/// <summary>
	/// Destroys a given object.
	/// </summary>
	/// <param name="obj">A pointer to the object to destroy.</param>
	void DestroyObject(_In_opt_ GameObject* obj);
	/// <summary>
	/// Searches the scene for an object with a given name.
	/// </summary>
	/// <param name="name">The name to search for.</param>
	/// <returns>A pointer to the game object, null if no object with the given name was found.</returns>
	_Success_(return != nullptr) _Check_return_ GameObject* FindObjectByName(_In_ const std::string& name) const;
	/// <summary>
	/// Sets the clear color of the scene.
	/// </summary>
	void SetClearColor(_In_ const ColorF& value);
	/// <summary>
	/// Sets the clear color of the scene.
	/// </summary>
	ColorF GetClearColor() const;
	/// <summary>
	/// Gets the managed counter part of this object.
	/// </summary>
	_Ret_notnull_ MonoObject* GetManagedObject() const;
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();

private:
	std::string m_name;
	std::vector<GameObject*> m_objects;
	ColorF m_clearColor;
	ResourceManager m_resources;
	MonoObject* m_managed;
	uint32_t m_handle;

	static MonoString* Mono_get_Name(MonoObject* obj);
	static ColorF Mono_get_ClearColor(MonoObject* obj);
	static void Mono_set_ClearColor(MonoObject* obj, ColorF* value);
	static MonoObject* Mono_get_ResourceManager(MonoObject* obj);
	static MonoObject* Mono_CreateObject(MonoObject* obj, MonoString* name);
	static MonoObject* Mono_FindObjectByName(MonoObject* obj, MonoString* name);
	static void Mono_DestroyObject(MonoObject* obj, MonoObject* object);
};