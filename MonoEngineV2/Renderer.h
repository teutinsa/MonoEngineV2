#pragma once
#include "Core.h"

#include "Vector2Int.h"

enum class CoordinateMode
{
	Default,
	PixelPerfect = Default,
	Normalized
};

enum class BufferType
{
	Default,
	Custom,
	BuiltIn = Default,
};

enum class RenderType
{
	D2D,
	D3D
};

class Renderer abstract
{
public:
	Renderer();

	static Renderer* GetCurrent();
	virtual void Begin() abstract;
	virtual void End() abstract;
	virtual void SetCoordinateMode(CoordinateMode value) abstract;
	virtual CoordinateMode GetCoordinateMode() const abstract;
	virtual void SetBufferType(BufferType value) abstract;
	virtual BufferType GetBufferType() const abstract;
	virtual void SetPixelSize(Vector2Int value) abstract;
	virtual Vector2Int GetPixelSize() const abstract;
	virtual RenderType GetRenderType() const abstract;

private:
	static Renderer* s_current;
};