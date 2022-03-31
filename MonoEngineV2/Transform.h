#pragma once
#include "Core.h"
#include "Vector2f.h"

class GameObject;

class Transform
{
public:
	/// <summary>
	/// The position of the transform.
	/// </summary>
	Vector2f position;
	/// <summary>
	/// The rotation angle of the transform in degrees.
	/// </summary>
	float rotation;
	/// <summary>
	/// The scale of the transform.
	/// </summary>
	Vector2f scale;
	/// <summary>
	/// The parent of the transform.
	/// </summary>
	Transform* parent;

	Transform(GameObject* obj);
	~Transform();

	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
	/// <summary>
	/// Gets the managed counter part of this object.
	/// </summary>
	/// <returns>A mono pointer to the object.</returns>
	_Ret_notnull_ MonoObject* GetManaged() const;
	D2D1_MATRIX_3X2_F GetMatrix() const;

private:
	MonoObject* m_managed;
	uint32_t m_handle;
	GameObject* m_object;
};