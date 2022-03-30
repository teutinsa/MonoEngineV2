#include "pch.h"
#include "ResourceManager.h"

#include "ResourceLoader2D.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (auto& kv : m_resources)
        delete kv.second;
    m_resources.clear();
}

void ResourceManager::RegisterIntCalls()
{
    ResourceLoader2D::RegisterIntCalls();
}

Resource* ResourceManager::GetResource(const std::string& name) const
{
    if (!m_resources.contains(name))
        return nullptr;
}

void ResourceManager::AddResource(const std::string& name, Resource* rsc)
{
}
