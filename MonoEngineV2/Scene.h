#pragma once

#include "GameObject.h"

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

private:
	std::string m_name;
	std::vector<GameObject*> m_objects;
};