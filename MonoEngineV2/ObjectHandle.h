#pragma once
#include "Core.h"

class ObjectHandle
{
public:
	ObjectHandle(_In_ MonoObject* obj);
	ObjectHandle(const ObjectHandle& other);
	ObjectHandle(ObjectHandle&& other) noexcept;
	~ObjectHandle();

	ObjectHandle& operator =(const ObjectHandle& other);
	ObjectHandle& operator =(ObjectHandle&& other);

	/// <summary>
	/// Get the managed object of this handle.
	/// </summary>
	_Ret_notnull_ MonoObject* GetObject() const;

private:
	MonoObject* m_obj;
	uint32_t m_handle;
};