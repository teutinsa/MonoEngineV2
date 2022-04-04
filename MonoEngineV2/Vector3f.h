#pragma once

struct Vector3f
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
	/// The Z coordinate of the vector.
	/// </summary>
	float z;

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	/// <param name="z">The Z value.</param>
	Vector3f(_In_ float x, _In_ float y, _In_ float z);
	/// <summary>
	/// Alternate constructor.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	/// <param name="z">The Z value.</param>
	Vector3f(_In_ float x, _In_ float y);
	Vector3f();
};