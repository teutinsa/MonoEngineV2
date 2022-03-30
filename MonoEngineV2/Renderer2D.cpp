#include "pch.h"
#include "Renderer2D.h"

#include "Window.h"

Renderer2D::Renderer2D(_In_ Window* wnd)
    : m_target(nullptr), m_wnd(wnd), m_buffer(nullptr), m_mode(CoordinateMode::Default), m_bufType(BufferType::Default)
{
    s_current = this;

    SIZE sz = wnd->GetClientSize();
    ThrowOnFail(s_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(wnd->GetHandle(), D2D1::SizeU(sz.cx, sz.cy), D2D1_PRESENT_OPTIONS_IMMEDIATELY), &m_target), "HWND render target creation failed!");
    ThrowOnFail(m_target->Resize(D2D1::SizeU(sz.cx, sz.cy)), "HWND render target resizing failed!");
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
    if (m_bufType == BufferType::Custom)
        return m_buffer;
    return m_target;
}

void Renderer2D::Begin()
{
    if (m_bufType == BufferType::Custom)
    {
        m_buffer->BeginDraw();
        m_buffer->Clear();
    }
    else
    {
        m_target->BeginDraw();
        m_target->Clear();
    }

    if (m_mode == CoordinateMode::Normalized)
        if (m_buffer != nullptr)
        {
            D2D1_SIZE_U sz = m_buffer->GetPixelSize();
            m_buffer->SetTransform(D2D1::Matrix3x2F::Identity() * D2D1::Matrix3x2F::Scale(sz.width, sz.height));
        }
        else
        {
            D2D1_SIZE_U sz = m_target->GetPixelSize();
            m_target->SetTransform(D2D1::Matrix3x2F::Identity() * D2D1::Matrix3x2F::Scale(sz.width, sz.height));
        }
}

void Renderer2D::End()
{
    if (m_bufType == BufferType::Custom)
    {
        ThrowOnFail(m_buffer->EndDraw(), "Ending of buffer draw call failed!");

        D2D1_SIZE_U tSz = m_target->GetPixelSize();
        D2D1_SIZE_U bSz = m_buffer->GetPixelSize();

        bool horizontal = bSz.width > tSz.width;
        float factor = horizontal ? ((float)tSz.width) / bSz.width : ((float)tSz.height) / bSz.height;

        D2D1_SIZE_F newSize = D2D1::SizeF(bSz.width * factor, bSz.height * factor);
        D2D1_POINT_2F pos = horizontal ? D2D1::Point2F(0.0f, tSz.height / 2 - newSize.height / 2) : D2D1::Point2F(tSz.width / 2 - newSize.width / 2);

        m_target->BeginDraw();
        m_target->Clear();

        ID2D1Bitmap* bmp = nullptr;
        ThrowOnFail(m_buffer->GetBitmap(&bmp), "Fetching of buffer bitmap failed!");
        m_target->DrawBitmap(bmp, D2D1::RectF(pos.x, pos.y, pos.x + newSize.width, pos.y + newSize.height), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, bSz.width, bSz.height));
        SafeRelease(bmp);
    }

    ThrowOnFail(m_target->EndDraw(), "Ending of draw call failed!");
}

void Renderer2D::SetCoordinateMode(_In_ CoordinateMode value)
{
    m_mode = value;
}

CoordinateMode Renderer2D::GetCoordinateMode() const
{
    return m_mode;
}

void Renderer2D::SetBufferType(_In_ BufferType value)
{
    switch (value)
    {
    case BufferType::Default:
        SafeRelease(m_buffer);
        break;

    case BufferType::Custom:
        SIZE sz = m_wnd->GetClientSize();
        D2D1_SIZE_U size = D2D1::SizeU(sz.cx, sz.cy);
        ThrowOnFail(m_target->CreateCompatibleRenderTarget(nullptr, &size, nullptr, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, &m_buffer), "Buffer creation failed!");
        break;
    }

    m_bufType = value;
}

BufferType Renderer2D::GetBufferType() const
{
    return m_bufType;
}

void Renderer2D::SetPixelSize(_In_ Vector2Int value)
{
    if (m_buffer != nullptr)
    {
        SafeRelease(m_buffer);

        D2D1_SIZE_U size = D2D1::SizeU(value.x, value.y);
        ThrowOnFail(m_target->CreateCompatibleRenderTarget(nullptr, &size, nullptr, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, &m_buffer), "Buffer creation failed!");

        SIZE sz = m_wnd->GetClientSize();
        ThrowOnFail(m_target->Resize(D2D1::SizeU(sz.cx, sz.cy)), "Target resizing failed!");
    }
    else
    {
        SafeRelease(m_buffer);

        ThrowOnFail(m_target->Resize(D2D1::SizeU(value.x, value.y)), "Target resizing failed!");
    }
}

Vector2Int Renderer2D::GetPixelSize() const
{
    D2D1_SIZE_U sz = m_target->GetPixelSize();
    return Vector2Int(sz.width, sz.height);
}

RenderType Renderer2D::GetRenderType() const
{
    return RenderType::D2D;
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