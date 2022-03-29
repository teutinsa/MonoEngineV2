#pragma once
#include "Core.h"

#include "IRenderer.h"

class Window;

class Renderer2D : public IRenderer
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

private:
	static Renderer2D* s_current;
	static ID2D1Factory* s_factory;
	static IDWriteFactory* s_writeFactory;
	static IWICImagingFactory* s_imageFactory;
	ID2D1HwndRenderTarget* m_target;
	Window* m_wnd;
	D2D1_MATRIX_3X2_F m_matNormal;

	STATIC_CTOR(Renderer2D);
};
