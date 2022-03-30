#pragma once
#include "Core.h"
#include "Vector2f.h"

struct Transform
{
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

	Transform();

	D2D1_MATRIX_3X2_F GetMatrix() const;
};