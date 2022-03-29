#include "pch.h"
#include "Transform.h"

Vector2f::Vector2f(_In_ float x, _In_ float y)
	: x(x), y(y)
{ }

Vector2f::Vector2f()
	: Vector2f(0.0f, 0.0f)
{ }

Transform::Transform()
	: position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), parent(nullptr)
{ }

D2D1_MATRIX_3X2_F Transform::GetMatrix() const
{
	D2D1_MATRIX_3X2_F m = parent != nullptr ? parent->GetMatrix() : D2D1::Matrix3x2F::Identity();
	return m * D2D1::Matrix3x2F::Translation(position.x, position.y)
		* D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(position.x, position.y))
		* D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y), D2D1::Point2F(position.x, position.y));
}
