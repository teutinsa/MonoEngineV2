#pragma once
#include "Core.h"
#include "Component.h"
#include "ResourceLoader2D.h"

#include "Vector2f.h"

class Components2D abstract sealed
{
public:
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
};

class ImageRenderer : public Component
{
public:
	ImageResource* image;
	Vector2f size;

	ImageRenderer();
	~ImageRenderer() override;

	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
	virtual size_t GetHash() const;
	void Render() override;
};

enum class ShapeType
{
	Rectangle,
	Ellipse,
	Line
};

class ShapeRenderer : public Component
{
public:
	BrushResource* brush;
	ShapeType shapeType;
	bool filled;
	Vector2f size;
	float strokeWidth;

	ShapeRenderer();
	~ShapeRenderer() override;

	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
	virtual size_t GetHash() const;
	void Render() override;

private:
	static MonoObject* Mono_get_Brush(MonoObject* obj);
	static void Mono_set_Brush(MonoObject* obj, MonoObject* value);
	static ShapeType Mono_get_ShapeType(MonoObject* obj);
	static void Mono_set_ShapeType(MonoObject* obj, ShapeType value);
	static bool Mono_get_Filled(MonoObject* obj);
	static void Mono_set_Filled(MonoObject* obj, bool value);
	static Vector2f Mono_get_Size(MonoObject* obj);
	static void Mono_set_Size(MonoObject* obj, Vector2f value);
	static float Mono_get_StrokeWidth(MonoObject* obj);
	static void Mono_set_StrokeWidth(MonoObject* obj, float value);
};

