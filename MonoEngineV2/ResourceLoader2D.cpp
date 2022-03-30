#include "pch.h"
#include "ResourceLoader2D.h"

#include "Renderer2D.h"
#include "ILRuntime.h"

ImageResource::ImageResource(_In_ const std::wstring& filename)
	: Resource(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "ImageResource"))
{
	if (Renderer::GetCurrent()->GetRenderType() != RenderType::D2D)
		throw std::runtime_error("Can't load a 2d resource if the render type is not set to 2d!");

	Renderer2D* r = (Renderer2D*)Renderer::GetCurrent();

	IWICBitmapDecoder* decoder = nullptr;
	ThrowOnFail(r->GetImageFactroy()->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder), "Decoder creation failed!");

	IWICBitmapFrameDecode* frame = nullptr;
	decoder->GetFrame(0, &frame);

	r->GetTarget()->CreateBitmapFromWicBitmap(frame, &m_bmp);

	SafeRelease(frame);
	SafeRelease(decoder);
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