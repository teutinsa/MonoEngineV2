#pragma once

#include "ResourceManager.h"

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
	/// <returns>A pointer to an image resource.</returns>
	_Success_(return != nullptr) _Check_return_ static ImageResource* LoadImageResource(_In_ ResourceManager* manager, _In_ const std::string& name, _In_ const std::wstring& filename);
	/// <summary>
	/// Loads a image from a memory buffer.
	/// </summary>
	/// <param name="manager">A pointer to a resource manager.</param>
	/// <param name="data">A pointer to the data.</param>
	/// <param name="size">The size of the data in bytes.</param>
	/// <returns>A pointer to an image resource.</returns>
	_Success_(return != nullptr) _Check_return_ static ImageResource* LoadImageResource(_In_ ResourceManager* manager, _In_ const std::string & name, _In_reads_bytes_(size) void* data, _In_ size_t size);

private:

};
