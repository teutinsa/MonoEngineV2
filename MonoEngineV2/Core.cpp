#include "pch.h"
#include "Core.h"

void DebugOut(_Printf_format_string_ const char* szFormat, ...)
{
    char buffer[1024];
    va_list arg;
    va_start(arg, szFormat);
    int num = _vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer), szFormat, arg);
    va_end(arg);

    if (num < 0)
        return;

    OutputDebugStringA(buffer);
}

void ThrowOnExc(_In_opt_ MonoException* exc)
{
    if (exc != nullptr)
        throw std::runtime_error(mono_string_to_utf8(mono_object_to_string((MonoObject*)exc, nullptr)));
}

std::string ComErrMsg(HRESULT hres)
{
    std::wstring ws = std::wstring(_com_error(hres).ErrorMessage());
    char buffer[512];
    wcstombs_s(nullptr, buffer, 512, ws.data(), ws.size());
    return buffer;
}
