#include "pch.h"
#include "Vector2Int.h"

Vector2Int::Vector2Int(_In_ int x, _In_ int y)
	: x(x), y(y)
{ }

Vector2Int::Vector2Int()
	: Vector2Int(0, 0)
{ }