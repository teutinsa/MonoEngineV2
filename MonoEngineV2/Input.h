#pragma once
#include "Core.h"

class Input
{
public:
	Input();

	/// <summary>
	/// Get the current Input instance.
	/// </summary>
	/// <returns>A pointer to the current Input instance.</returns>
	static Input* GetCurrent();
	/// <summary>
	/// Update
	/// </summary>
	void Update();
	/// <summary>
	/// Returns if a key is pressed.
	/// </summary>
	/// <param name="vk">The virtual key code.</param>
	/// <returns>True if the key is pressed, otherwise false.</returns>
	_Check_return_ bool GetKey(_In_ BYTE vk);
	/// <summary>
	/// Returns if a key was pressed.
	/// </summary>
	/// <param name="vk">The virtual key code.</param>
	/// <returns>True if the key was pressed in the current frame, otherwise false.</returns>
	_Check_return_ bool GetKeyDown(_In_ BYTE vk);
	/// <summary>
	/// Returns if a key was released.
	/// </summary>
	/// <param name="vk">The virtual key code.</param>
	/// <returns>True if the key was released in the current frame, otherwise false.</returns>
	_Check_return_ bool GetKeyUp(_In_ BYTE vk);
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();

private:
	static Input* s_current;
	BYTE state[256];
	BYTE prevState[256];

	static bool Mono_GetKey(BYTE* key);
	static bool Mono_GetKeyDown(BYTE* key);
	static bool Mono_GetKeyUp(BYTE* key);
};

