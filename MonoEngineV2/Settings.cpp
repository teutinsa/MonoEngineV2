#include "pch.h"
#include "Settings.h"

Settings::Settings(_In_ const std::string& filename)
	: m_filename(filename)
{ }

void Settings::WriteString(_In_ const std::string& section, _In_ const std::string& key, _In_ const std::string& value)
{
	WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), m_filename.c_str());
}

std::string Settings::ReadString(_In_ const std::string& section, _In_ const std::string& key, _In_ const std::string& def) const
{
	char buffer[512];
	GetPrivateProfileStringA(section.c_str(), key.c_str(), def.c_str(), buffer, 512, m_filename.c_str());
	return buffer;
}

void Settings::WriteStruct(_In_ const std::string& section, _In_ const std::string& key, _In_reads_bytes_(size) void* lpStruct, _In_ UINT size)
{
	WritePrivateProfileStructA(section.c_str(), key.c_str(), lpStruct, size, m_filename.c_str());
}

_Success_(return) _Check_return_
bool Settings::ReadStruct(_In_ const std::string& section, _In_ const std::string& key, _Out_writes_bytes_(size) void* lpStruct, _In_ UINT size)
{
	return GetPrivateProfileStructA(section.c_str(), key.c_str(), lpStruct, size, m_filename.c_str());
}
