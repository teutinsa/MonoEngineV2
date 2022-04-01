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

BrushResource::BrushResource(_In_ MonoClass* klass)
	: Resource(klass)
{ }

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

_Ret_notnull_
ID2D1Brush* SolidColorBrushResource::GetBrush() const
{
	return m_brush;
}

void ResourceLoader2D::RegisterIntCalls()
{
	ILRuntime::RegIntCall("MonoEngineV2Lib.ResourceLoader2D::LoadImage(MonoEngineV2Lib.ResourceManager,string,string)", Mono_LoadImage_filename);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ResourceLoader2D::LoadImage(MonoEngineV2Lib.ResourceManager,string,byte[])", Mono_LoadImage_data);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ResourceLoader2D::LoadSolidColorBrush", Mono_LoadSolidColorBrush);
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

_Success_(return != nullptr) _Check_return_
SolidColorBrushResource* ResourceLoader2D::LoadSolidColorBrushResource(_In_ ResourceManager* manager, _In_ const std::string& name, _In_ const ColorF& color)
{
	SolidColorBrushResource* brush = new SolidColorBrushResource(color);
	manager->AddResource(name, brush);
	return brush;
}

MonoObject* ResourceLoader2D::Mono_LoadImage_filename(MonoObject* manager, MonoString* name, MonoString* filename)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ResourceManager* m;
	mono_field_get_value(manager, nativeFld, &m);

	ImageResource* rsc = ResourceLoader2D::LoadImageResource(m, mono_string_to_utf8(name), mono_string_to_utf16(filename));
	return rsc->GetManagedObject();
}

MonoObject* ResourceLoader2D::Mono_LoadImage_data(MonoObject* manager, MonoString* name, MonoArray* data)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ResourceManager* m;
	mono_field_get_value(manager, nativeFld, &m);

	size_t length = mono_array_length(data);
	mono_byte* buffer = (mono_byte*)std::malloc(length);

	if (buffer == nullptr)
		return nullptr;

	for (size_t i = 0; i < length; i++)
		buffer[i] = mono_array_get(data, mono_byte, i);
	
	ImageResource* rsc = ResourceLoader2D::LoadImageResource(m, mono_string_to_utf8(name), buffer, length);

	std::free(buffer);

	return rsc->GetManagedObject();
}

MonoObject* ResourceLoader2D::Mono_LoadSolidColorBrush(MonoObject* manager, MonoString* name, ColorF color)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ResourceManager* m;
	mono_field_get_value(manager, nativeFld, &m);

	SolidColorBrushResource* rsc = ResourceLoader2D::LoadSolidColorBrushResource(m, mono_string_to_utf8(name), color);
	return rsc->GetManagedObject();
}