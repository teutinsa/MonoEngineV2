#include "pch.h"
#include "Window.h"

#define RECT_TO_SIZE(rc) { rc.right - rc.left, rc.bottom - rc.top }
#define WINDOW_NAME "MonoEngineWindow"

Window::Window()
	: m_handle(nullptr), closeAction(WindowCloseAction::Destroy)
{
	m_handle = CreateWindowExA(0, WINDOW_NAME, "", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(NULL), this);
}

Window::~Window()
{
	DestroyWindow(m_handle);
}

HWND Window::GetHandle() const
{
	return m_handle;
}

std::string Window::GetText() const
{
	char buffer[512];
	GetWindowTextA(m_handle, buffer, 512);
	return buffer;
}

void Window::SetText(_In_ const std::string& value)
{
	SetWindowTextA(m_handle, value.c_str());
}

DWORD Window::GetStyle() const
{
	return (DWORD)GetWindowLongA(m_handle, GWL_STYLE);
}

void Window::SetStyle(_In_ DWORD value)
{
	SetWindowLongA(m_handle, GWL_STYLE, (LONG)value);
}

DWORD Window::GetExStyle() const
{
	return (DWORD)GetWindowLongA(m_handle, GWL_EXSTYLE);
}

void Window::SetExStyle(_In_ DWORD value)
{
	SetWindowLongA(m_handle, GWL_EXSTYLE, (LONG)value);
}

void Window::AddSyle(_In_ DWORD value)
{
	SetStyle(GetStyle() | value);
}

void Window::RemoveSyle(_In_ DWORD value)
{
	SetStyle(GetStyle() & ~value);
}

SIZE Window::GetSize() const
{
	RECT rc;
	GetWindowRect(m_handle, &rc);
	return RECT_TO_SIZE(rc);
}

void Window::SetSize(_In_ SIZE value)
{
	SetWindowPos(m_handle, nullptr, 0, 0, value.cx, value.cy, SWP_NOMOVE | SWP_NOZORDER);
}

SIZE Window::GetClientSize() const
{
	RECT rc;
	GetClientRect(m_handle, &rc);
	return RECT_TO_SIZE(rc);
}

void Window::SetClientSize(_In_ SIZE value)
{
	RECT rc{ 0, 0, value.cx, value.cy };
	AdjustWindowRectEx(&rc, GetStyle(), false, GetExStyle());
	SetSize(RECT_TO_SIZE(rc));
}

void Window::Show()
{
	ShowWindow(m_handle, SW_SHOW);
}

void Window::Close()
{
	CloseWindow(m_handle);
}

void Window::Hide()
{
	ShowWindow(m_handle, SW_HIDE);
}

void Window::Minimize()
{
	ShowWindow(m_handle, SW_MINIMIZE);
}

void Window::Maximize()
{
	ShowWindow(m_handle, SW_MAXIMIZE);
}

LRESULT Window::WndProc(_In_ UINT msg, _In_ WPARAM wp, _In_ LPARAM lp)
{
	switch (msg)
	{
	case WM_CLOSE:
		switch (closeAction)
		{
		case WindowCloseAction::Destroy:
		case WindowCloseAction::Quit:
			DestroyWindow(m_handle);
			break;

		case WindowCloseAction::Hide:
			Hide();
			break;
		}
		return 0;

	case WM_DESTROY:
		if (closeAction == WindowCloseAction::Quit)
			PostQuitMessage(0);
		break;
	}

	return DefWindowProcA(m_handle, msg, wp, lp);
}

STATIC_CTOR_IMPL(Window)
{
	WNDCLASSEXA wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = &Window::BaseWndProc;
	wc.lpszClassName = WINDOW_NAME;

	RegisterClassExA(&wc);
}

_Success_(return != nullptr) 
Window* Window::GetFromHwnd(_In_ HWND hwnd, _In_ UINT msg, _In_ LPARAM lp)
{
	Window* tmp = nullptr;
	if (msg == WM_CREATE)
	{
		tmp = (Window*)((LPCREATESTRUCTA)lp)->lpCreateParams;
		SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)tmp);
	}
	else
		tmp = (Window*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
	return tmp;
}

LRESULT Window::BaseWndProc(_In_ HWND hwnd, _In_ UINT msg, _In_ WPARAM wp, _In_ LPARAM lp)
{
	Window* wnd = GetFromHwnd(hwnd, msg, lp);
	if (wnd != nullptr)
		return wnd->WndProc(msg, wp, lp);
	return DefWindowProcA(hwnd, msg, wp, lp);
}
