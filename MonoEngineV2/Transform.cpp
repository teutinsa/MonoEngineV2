#include "pch.h"
#include "Transform.h"

#include "ILRuntime.h"

Transform::Transform(GameObject* obj)
	: position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), parent(nullptr), m_object(obj)
{
	static MonoClass* transfCl;
	if (transfCl == nullptr)
		transfCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Transform");

	m_managed = ILRuntime::GetCurrent()->New(transfCl);
	m_handle = mono_gchandle_new(m_managed, false);

	static MonoClass* objectCl;
	if (objectCl == nullptr)
		objectCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object");
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(objectCl, "m_native");

	void* ptr = this;
	mono_field_set_value(m_managed, nativeFld, &ptr);
}

Transform::~Transform()
{
	mono_gchandle_free(m_handle);
}

void Transform::RegisterIntCalls()
{
}

_Ret_notnull_
MonoObject* Transform::GetManaged() const
{
	return m_managed;
}

D2D1_MATRIX_3X2_F Transform::GetMatrix() const
{
	D2D1_MATRIX_3X2_F m = parent != nullptr ? parent->GetMatrix() : D2D1::Matrix3x2F::Identity();
	return m * D2D1::Matrix3x2F::Translation(position.x, position.y)
		* D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(position.x, position.y))
		* D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y), D2D1::Point2F(position.x, position.y));
}
