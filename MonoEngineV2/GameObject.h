#pragma once
#include "Core.h"

#include "Transform.h"
#include "Component.h"

class Scene;

class GameObject
{
	friend class Scene;

public:
	Transform transform;

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="name">The name of the game object.</param>
	GameObject(_In_ const std::string& name);
	~GameObject();

	/// <summary>
	/// Update
	/// </summary>
	void Update();
	/// <summary>
	/// Render
	/// </summary>
	void Render();
	/// <summary>
	/// Get the scene this game object is in.
	/// </summary>
	/// <returns>A pointer to the scene.</returns>
	_Ret_ Scene* GetScene() const;
	/// <summary>
	/// Gets the name of the game object.
	/// </summary>
	std::string GetName() const;
	/// <summary>
	/// Add a component of 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	_Ret_notnull_ T* AddComponent()
	{
		static_assert(std::is_same_v(T, ScriptComponent), "Can't add a script component via this method!");
		Component* comp = new T();
		AddComponent(comp);
		return (T*)comp;
	}
	/// <summary>
	/// Removes a component from this game object.
	/// </summary>
	/// <param name="comp">A pointer of the component to remove.</param>
	void RemoveComonent(_In_opt_ const Component* comp);
	/// <summary>
	/// Tries to find a component with the given type and returns the first match.
	/// </summary>
	/// <typeparam name="T">The type to search for.</typeparam>
	/// <returns>A pointer to the found component, null no matching component was found.</returns>
	template<typename T>
	_Success_(return != nullptr) _Check_return_ _Ret_maybenull_ T* GetComponent() const
	{
		return (T*)GetComponent(Component::GetHash<T>());
	}
	/// <summary>
	/// Tries to find all components with the given type and returns the matches.
	/// </summary>
	/// <typeparam name="T">The type to search for.</typeparam>
	/// <returns>A std::vector containing pointers to the matching components.</returns>
	template<typename T>
	std::vector<T*> GetComponents() const
	{
		return (std::vector<T*>)GetComponents(Component::GetHash<T>())
	}

private:
	std::string m_name;
	Scene* m_scene;
	uint32_t m_handle;
	MonoObject* m_managed;
	std::vector<Component*> m_components;
	
	/// <summary>
	/// Adds a component to the game object.
	/// </summary>
	/// <param name="comp">The component to add</param>
	void AddComponent(_In_ Component* comp);
	/// <summary>
	/// Tries to find a component with the given hash and returns the first match.
	/// </summary>
	/// <param name="hash_code">The hash to search for.</param>
	/// <returns>A pointer to the found component, null no matching component was found.</returns>
	_Success_(return != nullptr) _Check_return_ _Ret_maybenull_ Component* GetComponent(_In_ size_t hash_code) const;
	/// <summary>
	/// Tries to find all components with the given hash and returns the matches.
	/// </summary>
	/// <param name="hash_code">The hash to search for.</param>
	/// <returns>A std::vector containing pointers to the matching components.</returns>
	std::vector<Component*> GetComponents(_In_ size_t hash_code) const;
};
