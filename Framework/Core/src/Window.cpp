#include "Pch.h"
#include "Window.h"

LRESULT CALLBACK WindowMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void xe::Core::Window::Initialize(HINSTANCE instance, std::wstring appName, uint32_t width, uint32_t height)
{
	m_instance = instance;
	m_appName = appName;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowMessageHandler;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // Standard icon
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = m_appName.c_str();
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	RECT rc = { 0, 0, (LONG)width, (LONG)height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	const int winWidth = std::min(static_cast<int>(rc.right - rc.left), screenWidth);
	const int winHeight = std::min(static_cast<int>(rc.bottom - rc.top), screenHeight);
	const int left = (screenWidth - winWidth) / 2;
	const int top = (screenHeight - winHeight) / 2;

	m_window = CreateWindow
	(
		m_appName.c_str(),
		m_appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		left, top,
		winWidth, winHeight,
		nullptr, nullptr,
		instance, nullptr
	);

	ShowWindow(m_window, SW_SHOWNORMAL);
	SetCursorPos(screenWidth / 2, screenHeight / 2);

	m_isActive = (m_window);

}

void xe::Core::Window::Terminate()
{
	DestroyWindow(m_window);

	UnregisterClass(m_appName.c_str(), m_instance);

	m_window = nullptr;
	m_instance = nullptr;
}

void xe::Core::Window::ProcessMessage()
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				m_isActive = false;
			}
	}
}
