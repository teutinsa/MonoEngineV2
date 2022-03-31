#include "pch.h"
#include "ResourceLoader2D.h"

#include "Renderer2D.h"
#include "ILRuntime.h"

ImageResource::ImageResource(_In_ const std::wstring& filename)
	: m_bmp(nullptr), Resource(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Image"))
{
	if (Renderer::GetCurrent()->GetRenderType() != RenderType::D2D)
		throw std::runtime_error("Can't load a 2d resource if the render type is not set to 2d!");

	Renderer2D* r = (Renderer2D*)Renderer::GetCurrent();

	IWICBitmapDecoder* decoder = nullptr;
	ThrowOnFail(r->GetImageFactroy()->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder), "Decoder creation failed!");

	IWICBitmapFrameDecode* frame = nullptr;
	ThrowOnFail(decoder->GetFrame(0, &frame), "Fetching of bitmap frame failed!");

	ThrowOnFail(r->GetTarget()->CreateBitmapFromWicBitmap(frame, &m_bmp), "Bitmap creation failed!");

	SafeRelease(frame);
	SafeRelease(decoder);
}

ImageResource::ImageResource(_In_reads_bytes_(size) void* data, _In_ size_t size)
	: m_bmp(nullptr), Resource(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Image"))
{
	if (Renderer::GetCurrent()->GetRenderType() != RenderType::D2D)
		throw std::runtime_error("Can't load a 2d resource if the render type is not set to 2d!");

	Renderer2D* r = (Renderer2D*)Renderer::GetCurrent();

	IWICStream* stream;
	ThrowOnFail(r->GetImageFactroy()->CreateStream(&stream), "Stream creation failed!");
	stream->InitializeFromMemory((WICInProcPointer)data, size);

	IWICBitmapDecoder* decoder;
	ThrowOnFail(r->GetImageFactroy()->CreateDecoderFromStream(stream, nullptr, WICDecodeMetadataCacheOnLoad, &decoder), "Decoder creation failed!");

	IWICBitmapFrameDecode* frame;
	ThrowOnFail(decoder->GetFrame(0, &frame), "Fetching of bitmap frame failed!");

	ThrowOnFail(r->GetTarget()->CreateBitmapFromWicBitmap(frame, &m_bmp), "Bitmap creation failed!");

	SafeRelease(frame);
	SafeRelease(decoder);
	SafeRelease(stream);
}

ImageResource::~ImageResource()
{
	SafeRelease(m_bmp);
	Resource::~Resource();
}

_Success_(return != nullptr) _Check_return_ _Ret_notnull_
ID2D1Bitmap* ImageResource::GetBitmap() const
{
	return m_bmp;
}

ResourceType ImageResource::GetType() const
{
	return ResourceType::Image2D;
}

ResourceType BrushResource::GetType() const
{
	return ResourceType::Brush2D;
}

SolidColorBrushResource::SolidColorBrushResource(_In_ ColorF color)
	: m_brush(nullptr), BrushResource(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "SolidColorBrush"))
{
	if (Renderer::GetCurrent()->GetRenderType() != RenderType::D2D)
		throw std::runtime_error("Can't load a 2d resource if the render type is not set to 2d!");

	Renderer2D* r = (Renderer2D*)Renderer::GetCurrent();

	r->GetTarget()->CreateSolidColorBrush(color, &m_brush);
}

SolidColorBrushResource::~SolidColorBrushResource()
{
	SafeRelease(m_brush);
	Resource::~Resource();
}

ID2D1Brush* SolidColorBrushResource::GetBrush() const
{
	return m_brush;
}

void ResourceLoader2D::RegisterIntCalls()
{

}

_Success_(return != nullptr) _Check_return_
ImageResource* ResourceLoader2D::LoadImageResource(_In_ ResourceManager* manager, _In_ const std::string& name, _In_ const std::wstring& filename)
{
	ImageResource* img = new ImageResource(filename);
	manager->AddResource(name, img);
	return img;
}

_Success_(return != nullptr) _Check_return_
ImageResource* ResourceLoader2D::LoadImageResource(_In_ ResourceManager* manager, _In_ const std::string & name, _In_reads_bytes_(size) void* data, _In_ size_t size)
{
	ImageResource* img = new ImageResource(data, size);
	manager->AddResource(name, img);
	return img;
}

BrushResource::BrushResource(_In_ MonoClass* klass)
	: Resource(klass)
{ }