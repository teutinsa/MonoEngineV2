#pragma once
#include "Core.h"

#include "Renderer.h"

class Window;

class Renderer2D : public Renderer
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="wnd">The target window for the renderer out put.</param>
	Renderer2D(_In_ Window* wnd);
	~Renderer2D();

	/// <summary>
	/// Gets the current 2D renderer instance.
	/// </summary>
	/// <returns>A pointer to the current 2D renderer instance.</returns>
	_Success_(return != nullptr) static Renderer2D* GetCurrent();
	/// <summary>
	/// Gets the current render target.
	/// </summary>
	/// <returns>A pointer to the current render target.</returns>
	_Success_(return != nullptr) ID2D1RenderTarget* GetTarget() const;
	/// <summary>
	/// Begins the rendering cycle.
	/// </summary>
	void Begin();
	/// <summary>
	/// Ends the rendering cycle.
	/// </summary>
	void End();
	/// <summary>
	/// Sets the coordinate mode.
	/// </summary>
	void SetCoordinateMode(_In_ CoordinateMode value);
	/// <summary>
	/// Gets the coordinate mode.
	/// </summary>
	CoordinateMode GetCoordinateMode() const;
	/// <summary>
	/// Sets the buffer type of this renderer.
	/// </summary>
	void SetBufferType(_In_ BufferType value);
	/// <summary>
	/// Gets the buffer type of this renderer.
	/// </summary>
	BufferType GetBufferType() const;
	/// <summary>
	/// Sets the size of the buffer.
	/// </summary>
	void SetPixelSize(_In_ Vector2Int value);
	/// <summary>
	/// Gets the size of the buffer.
	/// </summary>
	Vector2Int GetPixelSize() const;
	/// <summary>
	/// Gets the render type of this renderer.
	/// </summary>
	RenderType GetRenderType() const;
	/// <summary>
	/// Gets the image factory for this renderer.
	/// </summary>
	_Success_(return != nullptr) static IWICImagingFactory* GetImageFactroy();

private:
	static Renderer2D* s_current;
	static ID2D1Factory* s_factory;
	static IDWriteFactory* s_writeFactory;
	static IWICImagingFactory* s_imageFactory;
	ID2D1HwndRenderTarget* m_target;
	ID2D1BitmapRenderTarget* m_buffer;
	Window* m_wnd;
	CoordinateMode m_mode;
	BufferType m_bufType;

	STATIC_CTOR(Renderer2D);
};
