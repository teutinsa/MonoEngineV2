#include "pch.h"
#include "Input.h"

#include "ILRuntime.h"

Input::Input()
{
	s_current = this;

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
	ILRuntime::RegIntCall("MonoEngineV2Lib.Input::GetKey", Mono_GetKey);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Input::GetKeyDown", Mono_GetKeyDown);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Input::GetKeyUp", Mono_GetKeyUp);
}

bool Input::Mono_GetKey(BYTE key)
{
	return Input::GetCurrent()->GetKey(key);
}

bool Input::Mono_GetKeyDown(BYTE key)
{
	return Input::GetCurrent()->GetKeyDown(key);
}

bool Input::Mono_GetKeyUp(BYTE key)
{
	return Input::GetCurrent()->GetKeyUp(key);
}

Input* Input::s_current;