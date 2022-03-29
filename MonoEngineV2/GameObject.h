#pragma once
#include "Core.h"

#include "Transform.h"

class GameObject
{
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

private:
	std::string m_name;
};
