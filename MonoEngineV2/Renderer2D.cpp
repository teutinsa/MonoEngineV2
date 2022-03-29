#include "pch.h"
#include "Renderer2D.h"

#include "Window.h"

Renderer2D::Renderer2D(_In_ Window* wnd)
    : m_target(nullptr), m_wnd(wnd)
{
    s_current = this;

    ThrowOnFail(s_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(wnd->GetHandle()), &m_target), "HWND render target creation failed!");
    SIZE sz = wnd->GetClientSize();
    ThrowOnFail(m_target->Resize(D2D1::SizeU(sz.cx, sz.cy)), "HWND render target resizing failed!");

    m_matNormal = D2D1::Matrix3x2F::Identity() * D2D1::Matrix3x2F::Scale((FLOAT)sz.cx, (FLOAT)sz.cy);
}

Renderer2D::~Renderer2D()
{
    SafeRelease(m_target);
}

_Success_(return != nullptr)
Renderer2D* Renderer2D::GetCurrent()
{
    return s_current;
}

_Success_(return != nullptr)
ID2D1RenderTarget* Renderer2D::GetTarget() const
{
    return m_target;
}

void Renderer2D::Begin()
{
    m_target->BeginDraw();
    m_target->Clear();
}

void Renderer2D::End()
{
    ThrowOnFail(m_target->EndDraw(), "Ending of draw call failed!");
}

Renderer2D* Renderer2D::s_current;
ID2D1Factory* Renderer2D::s_factory;
IDWriteFactory* Renderer2D::s_writeFactory;
IWICImagingFactory* Renderer2D::s_imageFactory;

STATIC_CTOR_IMPL(Renderer2D)
{
    ThrowOnFail(CoInitialize(nullptr), "COM initialization failed!"); //Initialize COM

    ThrowOnFail(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &s_factory), "Direct 2D factory creation failed!");
    ThrowOnFail(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&s_writeFactory), "Direct write factory creation failed!");
    ThrowOnFail(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&s_imageFactory)), "Image factory creation failed!");
}