#pragma once
#include "Core.h"

enum class ResourceType
{
	Unknown,
	Image2D,
	Brush2D
};

class Resource abstract
{
public:
	Resource(MonoClass* klass);
	virtual ~Resource();

	virtual ResourceType GetType() const abstract;
	_Ret_notnull_ MonoObject* GetManagedObject() const;

private:
	MonoClass* m_class;
	MonoObject* m_managed;
	uint32_t m_handle;
};