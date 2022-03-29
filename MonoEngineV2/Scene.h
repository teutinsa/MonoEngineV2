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

private:
	std::string m_name;
	std::vector<GameObject*> m_objects;
};