#ifndef __XE_CORE_WINDOW_H__
#define __XE_CORE_WINDOW_H__

namespace xe::Core
{
	class Window
	{
		HINSTANCE _instance = nullptr;
		HWND _window = nullptr;
		std::wstring _appName;
		bool _isActive = false;

	public:
		void Initialize(HINSTANCE instance, std::wstring appName, uint32_t width, uint32_t height);
		void Terminate();

		void ProcessMessage();

		HWND GetWindowHandle() const { return _window; }
		bool IsActive() const { return _isActive; }
	};
}

#endif
