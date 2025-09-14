#include "Window.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace arc
{
	class Win32Window : public AppWindow
	{
	private:
		IAppWindowInterface* mInterface = nullptr;

		HWND mWindowHandle = NULL;
	public:
		Win32Window(const AppWindowInfo& Info, IAppWindowInterface* pInterface) 
			:mInterface(pInterface)
		{
			WNDCLASS wc = {};
			wc.lpfnWndProc = Win32WindowProc;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.lpszClassName = "ArcWin32Window";
			wc.style = CS_OWNDC;

			RegisterClassA(&wc);

			mWindowHandle = CreateWindowExA(0, wc.lpszClassName, Info.title,
				WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				Info.width, Info.height, nullptr, nullptr, wc.hInstance, this);

			if (mInterface)
				mInterface->OnWindowCreate(this);
			
			ShowWindow(mWindowHandle, SW_SHOW);
		}

		~Win32Window() override
		{
			DestroyWindow(mWindowHandle);
		}

		u64 GetHandle() const override
		{
			return (u64)mWindowHandle;
		}

		static LRESULT Win32WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			Win32Window* appWindow = nullptr;

			if (msg == WM_CREATE)
			{
				CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
				appWindow = reinterpret_cast<Win32Window*>(cs->lpCreateParams);

				SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(appWindow));
			}
			else
			{
				appWindow = reinterpret_cast<Win32Window*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
			}

			switch (msg)
			{
			case WM_DESTROY:
			{
				if (appWindow->mInterface)
					appWindow->mInterface->OnWindowDestroy(appWindow);
			
				break;
			}
			default:
				return DefWindowProcA(hwnd, msg, wParam, lParam);
			}

			return 0;
		}
	};
}

namespace arc
{
	shared<AppWindow> window::Create(const AppWindowInfo& Info, IAppWindowInterface* pInterface)
	{
		return MakeShared<Win32Window>(Info, pInterface);
	}

	void window::Tick()
	{
		MSG msg = {};
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
}