#include "pch.h"
#include "Components2D.h"

#include "ILRuntime.h"2
#include "Renderer2D.h"

void Components2D::RegisterIntCalls()
{
	ImageRenderer::RegisterIntCalls();
	ShapeRenderer::RegisterIntCalls();
}

ImageRenderer::ImageRenderer()
	: Component(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "ImageRenderer")), image(nullptr), interpolate(true), opacity(1.0f)
{
}

ImageRenderer::~ImageRenderer()
{
	Component::~Component();
}

void ImageRenderer::RegisterIntCalls()
{
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::get_Image", Mono_get_Image);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::set_Image", Mono_set_Image);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::get_Size", Mono_get_Size);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::set_Size", Mono_set_Size);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::get_Interpolate", Mono_get_Interpolate);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::set_Interpolate", Mono_set_Interpolate);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::get_Opacity", Mono_get_Opacity);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ImageRenderer::set_Opacity", Mono_set_Opacity);
}

size_t ImageRenderer::GetHash() const
{
	return typeid(ImageRenderer).hash_code();
}

void ImageRenderer::Render()
{
	if (image == nullptr)
		return;

	Renderer2D* r = (Renderer2D*)Renderer::GetCurrent();
	ID2D1RenderTarget* t = r->GetTarget();

	D2D1_RECT_F rect = D2D1::RectF(-size.x / 2, -size.y / 2, (-size.x / 2) + size.x, (-size.y / 2) + size.y);
	D2D1_SIZE_U sz = image->GetBitmap()->GetPixelSize();

	t->DrawBitmap(image->GetBitmap(), rect, opacity, interpolate ? D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, sz.width, sz.height));
}

MonoObject* ImageRenderer::Mono_get_Image(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->image->GetManagedObject();
}

void ImageRenderer::Mono_set_Image(MonoObject* obj, MonoObject* value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);
	
	ImageResource* img;
	mono_field_get_value(value, nativeFld, &img);

	r->image = img;
}

Vector2f ImageRenderer::Mono_get_Size(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->size;
}

void ImageRenderer::Mono_set_Size(MonoObject* obj, Vector2f value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->size = value;
}

bool ImageRenderer::Mono_get_Interpolate(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->interpolate;
}

void ImageRenderer::Mono_set_Interpolate(MonoObject* obj, bool value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->interpolate = value;
}

float ImageRenderer::Mono_get_Opacity(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->opacity;
}

void ImageRenderer::Mono_set_Opacity(MonoObject* obj, float value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ImageRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->opacity = value;
}

ShapeRenderer::ShapeRenderer()
	: Component(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "ShapeRenderer")), brush(nullptr), shapeType(ShapeType::Rectangle), filled(true), strokeWidth(1.0f)
{
}

ShapeRenderer::~ShapeRenderer()
{
	Component::~Component();
}

void ShapeRenderer::RegisterIntCalls()
{
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::get_Brush", Mono_get_Brush);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::set_Brush", Mono_set_Brush);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::get_ShapeType", Mono_get_ShapeType);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::set_ShapeType", Mono_set_ShapeType);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::get_Filled", Mono_get_Filled);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::set_Filled", Mono_set_Filled);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::get_Size", Mono_get_Size);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::set_Size", Mono_set_Size);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::get_StrokeWidth", Mono_get_StrokeWidth);
	ILRuntime::RegIntCall("MonoEngineV2Lib.ShapeRenderer::set_StrokeWidth", Mono_set_StrokeWidth);
}

void ShapeRenderer::Render()
{
	if (brush == nullptr)
		return;

	Renderer2D* r = (Renderer2D*)Renderer::GetCurrent();
	ID2D1RenderTarget* t = r->GetTarget();

	D2D1_RECT_F rect = D2D1::RectF(-size.x / 2, -size.y / 2, (-size.x / 2) + size.x, (-size.y / 2) + size.y);

	if (shapeType == ShapeType::Line)
	{
		t->DrawLine(D2D1::Point2F(), D2D1::Point2F(size.x, size.y), brush->GetBrush(), strokeWidth);
		return;
	}

	if (filled)
	{
		switch (shapeType)
		{
		case ShapeType::Rectangle:
			t->FillRectangle(&rect, brush->GetBrush());
			break;

		case ShapeType::Ellipse:
			t->FillEllipse(D2D1::Ellipse(D2D1::Point2F(), size.x, size.y), brush->GetBrush());
			break;
		}
	}
	else
	{
		switch (shapeType)
		{
		case ShapeType::Rectangle:
			t->DrawRectangle(&rect, brush->GetBrush(), strokeWidth);
			break;

		case ShapeType::Ellipse:
			t->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(), size.x, size.y), brush->GetBrush(), strokeWidth);
			break;
		}
	}
}

size_t ShapeRenderer::GetHash() const
{
	return typeid(ShapeRenderer).hash_code();
}

MonoObject* ShapeRenderer::Mono_get_Brush(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	if(r->brush == nullptr)
		return nullptr;
	return r->brush->GetManagedObject();
}

void ShapeRenderer::Mono_set_Brush(MonoObject* obj, MonoObject* value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	BrushResource* b;
	mono_field_get_value(value, nativeFld, &b);

	r->brush = b;
}

ShapeType ShapeRenderer::Mono_get_ShapeType(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);
	
	return r->shapeType;
}

void ShapeRenderer::Mono_set_ShapeType(MonoObject* obj, ShapeType value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->shapeType = value;
}

bool ShapeRenderer::Mono_get_Filled(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->filled;
}

void ShapeRenderer::Mono_set_Filled(MonoObject* obj, bool value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->filled = value;
}

Vector2f ShapeRenderer::Mono_get_Size(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->size;
}

void ShapeRenderer::Mono_set_Size(MonoObject* obj, Vector2f value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->size = value;
}

float ShapeRenderer::Mono_get_StrokeWidth(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	return r->strokeWidth;
}

void ShapeRenderer::Mono_set_StrokeWidth(MonoObject* obj, float value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	ShapeRenderer* r;
	mono_field_get_value(obj, nativeFld, &r);

	r->strokeWidth = value;
}
