#pragma once

struct Vector2Int
{
	/// <summary>
	/// The X coordinate of the vector.
	/// </summary>
	int x;
	/// <summary>
	/// The Y coordinate of the vector.
	/// </summary>
	int y;

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	Vector2Int(_In_ int x, _In_ int y);
	Vector2Int();
};