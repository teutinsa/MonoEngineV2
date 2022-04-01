#pragma once
#include "pch.h"

#include <sal.h> //Import SAL annotations (_In_, _Out_, ...)

#ifdef _DEBUG
#define PATH "C:\\Programming\\Engines\\MonoEngineV2\\x64\\Debug"
#else
#define PATH "."
#endif

#define T_CALLOC(type) ((type*)std::calloc(1, sizeof(type)))
#define T_MALLOC(type) ((type*)std::malloc(sizeof(type)))
#define T_FREE(ptr) if(ptr != nullptr) std::free(ptr); ptr = nullptr

#define SafeDel(ptr) if(ptr != nullptr) delete ptr; ptr = nullptr
#define SafeRelease(ptr) if(ptr != nullptr) ptr->Release(); ptr = nullptr

struct _static_ctor_
{
	_static_ctor_(void(*func)())
	{
		func();
	}
};

#define STATIC_CTOR(type) \
static _static_ctor_ __staticCtor; \
static void _StaticCtor()

#define STATIC_CTOR_IMPL(type) \
_static_ctor_ type::__staticCtor(type::_StaticCtor); \
void type::_StaticCtor()

#define _ToString(x) #x
#define ToString(x) _ToString(x)

#define ThrowOnFail(expr, msg) { HRESULT res = expr; if(FAILED(res)) throw std::runtime_error(std::string(__FILE__) +  std::string(":\n") + std::string(__FUNCTION__) + std::string("\n=> ") + std::string(#expr) + std::string("\n\nCOM err: ") + ComErrMsg(res) + std::string("\n\nMessage: ") + std::string(#msg)); }

/// <summary>
/// Writes a debug message to the visual studio output.
/// </summary>
void DebugOut(_Printf_format_string_ const char* szFormat, ...);

void ThrowOnExc(_In_opt_ MonoException* exc);

std::string ComErrMsg(HRESULT hres);