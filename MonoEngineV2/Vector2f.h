#pragma once

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