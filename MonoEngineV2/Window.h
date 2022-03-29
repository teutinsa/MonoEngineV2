#pragma once
#include "Core.h"

enum class WindowCloseAction
{
	/// <summary>
	/// The window gets destroyed upon closing.
	/// </summary>
	Destroy,
	/// <summary>
	/// The window gets destroyed upon closing, and the quit message gets posted.
	/// </summary>
	Quit,
	/// <summary>
	/// The window gets hidden upon closing.
	/// </summary>
	Hide,
	/// <summary>
	/// Nothing happens when closing the window.
	/// </summary>
	None
};

class Window
{
public:
	/// <summary>
	/// The action to be performed when closing the window.
	/// </summary>
	WindowCloseAction closeAction;

	/// <summary>
	/// Default constructor.
	/// </summary>
	Window();
	~Window();

	/// <summary>
	/// Gets the window handle.
	/// </summary>
	HWND GetHandle() const;
	/// <summary>
	/// Gets the window text. (Usually the text in the title bar)
	/// </summary>
	std::string GetText() const;
	/// <summary>
	/// Sets the window text.
	/// </summary>
	void SetText(_In_ const std::string& value);
	/// <summary>
	/// Gets the window style.
	/// </summary>
	DWORD GetStyle() const;
	/// <summary>
	/// Sets the window style.
	/// </summary>
	void SetStyle(_In_ DWORD value);
	/// <summary>
	/// Gets the extended window style.
	/// </summary>
	DWORD GetExStyle() const;
	/// <summary>
	/// Sets the extended window style.
	/// </summary>
	void SetExStyle(_In_ DWORD value);
	/// <summary>
	/// Adds the given style to the current window style.
	/// </summary>
	/// <param name="value">The style to add.</param>
	void AddSyle(_In_ DWORD value);
	/// <summary>
	/// Removes the given style to the current window style.
	/// </summary>
	/// <param name="value">The style to remove.</param>
	void RemoveSyle(_In_ DWORD value);
	/// <summary>
	/// Gets the size of the window.
	/// </summary>
	SIZE GetSize() const;
	/// <summary>
	/// Sets the size of the window.
	/// </summary>
	void SetSize(_In_ SIZE value);
	/// <summary>
	/// Gets the size of the client area.
	/// </summary>
	SIZE GetClientSize() const;
	/// <summary>
	/// Sets the size of the client area.
	/// </summary>
	void SetClientSize(_In_ SIZE value);
	/// <summary>
	/// Shows the window.
	/// </summary>
	void Show();
	/// <summary>
	/// Closes the window.
	/// </summary>
	void Close();
	/// <summary>
	/// Hides the window.
	/// </summary>
	void Hide();
	/// <summary>
	/// Minimizes the window.
	/// </summary>
	void Minimize();
	/// <summary>
	/// Maximizes the window.
	/// </summary>
	void Maximize();

protected:
	LRESULT WndProc(_In_ UINT msg, _In_ WPARAM wp, _In_ LPARAM lp);

private:
	HWND m_handle;

	STATIC_CTOR(Window);

	/// <summary>
	/// Stores an retrieves a pointer to a Window object in the user data of the HWND.
	/// </summary>
	/// <param name="hwnd">The target HWND.</param>
	/// <param name="msg">The current message.</param>
	/// <param name="lp">The current long parameter.</param>
	/// <returns>A pointer to the Window object associated with the HWND. May be null in some cases.</returns>
	_Success_(return != nullptr) _Check_return_ static Window* GetFromHwnd(_In_ HWND hwnd, _In_ UINT msg, _In_ LPARAM lp);
	static LRESULT CALLBACK BaseWndProc(_In_ HWND hwnd, _In_ UINT msg, _In_ WPARAM wp, _In_ LPARAM lp);
};

