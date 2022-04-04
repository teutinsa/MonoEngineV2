#include "pch.h"
#include "Vector3f.h"

Vector3f::Vector3f(_In_ float x, _In_ float y, _In_ float z)
	: x(x), y(y), z(z)
{ }

Vector3f::Vector3f(_In_ float x, _In_ float y)
	: x(x), y(y), z(0.0f)
{ }

Vector3f::Vector3f()
	: Vector3f(0.0f, 0.0f, 0.0f)
{ }
