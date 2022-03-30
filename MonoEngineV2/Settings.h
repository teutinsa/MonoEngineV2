#pragma once

class Settings
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="filename">The file name to the settings file.</param>
	Settings(_In_ const std::string& filename);

	/// <summary>
	/// Writes a string to a given section and key.
	/// </summary>
	/// <param name="section">The target section.</param>
	/// <param name="key">The target key.</param>
	/// <param name="value">The string value.</param>
	void WriteString(_In_ const std::string& section, _In_ const std::string& key, _In_ const std::string& value);
	/// <summary>
	/// Reads a string from a given section and key.
	/// </summary>
	/// <param name="section">The target section.</param>
	/// <param name="key">The target key.</param>
	/// <param name="def">The default value, in case the key or section does not exist.</param>
	/// <returns>The read string value.</returns>
	std::string ReadString(_In_ const std::string& section, _In_ const std::string& key, _In_ const std::string& def) const;
	/// <summary>
	/// Writes the binary data to a given section an key.
	/// </summary>
	/// <param name="section">The target section.</param>
	/// <param name="key">The target key.</param>
	/// <param name="lpStruct">A pointer to read the data from.</param>
	/// <param name="size">The size of the data in bytes.</param>
	void WriteStruct(_In_ const std::string& section, _In_ const std::string& key, _In_reads_bytes_(size) void* lpStruct, _In_ UINT size);
	/// <summary>
	/// Reads the binary data from a given section an key.
	/// </summary>
	/// <param name="section">The target section.</param>
	/// <param name="key">The target key.</param>
	/// <param name="lpStruct">A pointer to write the data to.</param>
	/// <param name="size">The size of the data in bytes.</param>
	/// <returns>True if the function succeeds, otherwise false.</returns>
	_Success_(return) _Check_return_ bool ReadStruct(_In_ const std::string& section, _In_ const std::string& key, _Out_writes_bytes_(size) void* lpStruct, _In_ UINT size);
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();

private:
	std::string m_filename;
};