#pragma once

#include "ResourceManager.h"
#include "ColorF.h"

class ImageResource : public Resource
{
public:
	ImageResource(_In_ const std::wstring& filename);
	ImageResource(_In_reads_bytes_(size) void* data, _In_ size_t size);
	~ImageResource() override;

	/// <summary>
	/// Gets the bitmap of this image resource.
	/// </summary>
	_Success_(return != nullptr) _Check_return_ _Ret_notnull_ ID2D1Bitmap* GetBitmap() const;
	ResourceType GetType() const;

private:
	ID2D1Bitmap* m_bmp;
};

class BrushResource abstract : public Resource
{
public:
	BrushResource(_In_ MonoClass* klass);

	/// <summary>
	/// Gets the brush of this resource.
	/// </summary>
	_Ret_notnull_ virtual ID2D1Brush* GetBrush() const abstract;
	ResourceType GetType() const;
};

class SolidColorBrushResource : public BrushResource
{
public:
	SolidColorBrushResource(_In_ ColorF color);
	~SolidColorBrushResource() override;

	ID2D1Brush* GetBrush() const;

private:
	ID2D1SolidColorBrush* m_brush;
};

class ResourceLoader2D abstract sealed
{
public:
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
	/// <summary>
	/// Loads a image from a file.
	/// </summary>
	/// <param name="manager">A pointer to a resource manager.</param>
	/// <param name="name">The name of the resource.</param>
	/// <param name="filename">The name and path of the image file.</param>
	/// <returns>A pointer to an image resource.</returns>
	_Success_(return != nullptr) _Check_return_ static ImageResource* LoadImageResource(_In_ ResourceManager* manager, _In_ const std::string& name, _In_ const std::wstring& filename);
	/// <summary>
	/// Loads a image from a memory buffer.
	/// </summary>
	/// <param name="manager">A pointer to a resource manager.</param>
	/// <param name="name">The name of the resource.</param>
	/// <param name="data">A pointer to the data.</param>
	/// <param name="size">The size of the data in bytes.</param>
	/// <returns>A pointer to an image resource.</returns>
	_Success_(return != nullptr) _Check_return_ static ImageResource* LoadImageResource(_In_ ResourceManager* manager, _In_ const std::string& name, _In_reads_bytes_(size) void* data, _In_ size_t size);
	/// <summary>
	/// Loads a solid color brush.
	/// </summary>
	/// <param name="manager">A pointer to a resource manager.</param>
	/// <param name="name">The name of the resource.</param>
	/// <param name="color">The color for the solid brush.</param>
	/// <returns>A pointer to a solid brush resource.</returns>
	_Success_(return != nullptr) _Check_return_ static SolidColorBrushResource* LoadSolidColorBrushResource(_In_ ResourceManager* manager, _In_ const std::string& name, _In_ const ColorF& color);

private:
	static MonoObject* Mono_LoadImage_filename(MonoObject* manager, MonoString* name, MonoString* filename);
	static MonoObject* Mono_LoadImage_data(MonoObject* manager, MonoString* name, MonoArray* data);
	static MonoObject* Mono_LoadSolidColorBrush(MonoObject* manager, MonoString* name, ColorF color);
};
