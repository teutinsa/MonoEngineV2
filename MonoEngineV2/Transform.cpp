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
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::get_Position", Mono_get_Position);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::set_Position", Mono_set_Position);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::get_Rotation", Mono_get_Rotation);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::set_Rotation", Mono_set_Rotation);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::get_Scale", Mono_get_Scale);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::set_Scale", Mono_set_Scale);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::get_Parent", Mono_get_Parent);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Transform::set_Parent", Mono_set_Parent);
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

Vector3f Transform::Mono_get_Position(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	return t->position;
}

void Transform::Mono_set_Position(MonoObject* obj, Vector3f value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	t->position = value;
}

float Transform::Mono_get_Rotation(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	return t->rotation;
}

void Transform::Mono_set_Rotation(MonoObject* obj, float value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	t->rotation = value;
}

Vector3f Transform::Mono_get_Scale(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	return t->scale;
}

void Transform::Mono_set_Scale(MonoObject* obj, Vector3f value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	t->scale = value;
}

MonoObject* Transform::Mono_get_Parent(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	return t->parent->GetManaged();
}

void Transform::Mono_set_Parent(MonoObject* obj, MonoObject* value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Transform* t;
	mono_field_get_value(obj, nativeFld, &t);

	Transform* t2;
	mono_field_get_value(value, nativeFld, &t2);

	t->parent = t2;
}
