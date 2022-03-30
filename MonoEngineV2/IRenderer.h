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

__interface IRenderer
{
	void Begin();
	void End();
	void SetCoordinateMode(CoordinateMode value);
	CoordinateMode GetCoordinateMode() const;
	void SetBufferType(BufferType value);
	BufferType GetBufferType() const;
	void SetPixelSize(Vector2Int value);
	Vector2Int GetPixelSize() const;
};