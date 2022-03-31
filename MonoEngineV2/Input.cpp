#include "pch.h"
#include "Input.h"

Input::Input()
{
	ZeroMemory(state, 256);
	ZeroMemory(prevState, 256);
}

Input* Input::GetCurrent()
{
	return s_current;
}

void Input::Update()
{
	std::memcpy(prevState, state, 256);
	bool res = GetKeyboardState(state);
}

_Check_return_
bool Input::GetKey(_In_ BYTE vk)
{
	return (bool)state[vk];
}

_Check_return_
bool Input::GetKeyDown(_In_ BYTE vk)
{
	return (bool)state[vk] && !(bool)prevState[vk];
}

_Check_return_
bool Input::GetKeyUp(_In_ BYTE vk)
{
	return !(bool)state[vk] && (bool)prevState[vk];
}

void Input::RegisterIntCalls()
{
}

Input* Input::s_current;