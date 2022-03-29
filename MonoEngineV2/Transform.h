#pragma once
#include "Core.h"

struct Vector2f
{
	/// <summary>
	/// The X coordinate of the vector.
	/// </summary>
	float x;
	/// <summary>
	/// The Y coordinate of the vector.
	/// </summary>
	float y;

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	Vector2f(_In_ float x, _In_ float y);
	Vector2f();
};

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