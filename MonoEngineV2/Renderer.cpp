#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
{
    s_current = this;
}

Renderer* Renderer::GetCurrent()
{
    return s_current;
}

Renderer* Renderer::s_current;
