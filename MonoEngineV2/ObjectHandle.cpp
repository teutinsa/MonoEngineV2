#include "pch.h"
#include "ObjectHandle.h"

ObjectHandle::ObjectHandle(_In_ MonoObject* obj)
    : m_obj(obj)
{
    m_handle = mono_gchandle_new(obj, false);
}

ObjectHandle::ObjectHandle(const ObjectHandle& other)
    : ObjectHandle(other.m_obj)
{ }

ObjectHandle::ObjectHandle(ObjectHandle&& other) noexcept
{
    m_obj = other.m_obj;
    m_handle = other.m_handle;

    other.m_obj = nullptr;
    other.m_handle = 0;
}

ObjectHandle::~ObjectHandle()
{
    if(m_handle != 0U)
        mono_gchandle_free(m_handle);
}

ObjectHandle& ObjectHandle::operator=(const ObjectHandle& other)
{
    mono_gchandle_free(m_handle);
    m_obj = other.m_obj;
    m_handle = mono_gchandle_new(m_obj, false);

    return *this;
}

ObjectHandle& ObjectHandle::operator=(ObjectHandle&& other)
{
    mono_gchandle_free(m_handle);

    m_obj = other.m_obj;
    m_handle = other.m_handle;

    other.m_obj = nullptr;
    other.m_handle = 0;

    return *this;
}

_Ret_notnull_ MonoObject* ObjectHandle::GetObject() const
{
    return m_obj;
}
