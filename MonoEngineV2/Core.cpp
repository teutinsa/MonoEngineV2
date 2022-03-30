#include "pch.h"
#include "Core.h"

void DebugOut(const char* szFormat, ...)
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
