#include "pch.h"
#include "Vector2f.h"

Vector2f::Vector2f(_In_ float x, _In_ float y)
	: x(x), y(y)
{ }

Vector2f::Vector2f()
	: Vector2f(0.0f, 0.0f)
{ }
