#include "GraphicsDevice.h"
#include "OpenGLGraphicsDevice.h"

#include "OpenGLProc.h"

namespace arc
{
	struct Win32WindowContext
	{
		HWND hwnd;
		HDC hdc;
		HGLRC hglrc;
		i32 pixelFormat;

		~Win32WindowContext()
		{
			
		}
	};

	struct OpenGLGraphicsDevice::IMPL
	{
		std::list<Win32WindowContext> mContextList;
	};

	OpenGLGraphicsDevice::OpenGLGraphicsDevice()
		:mImpl(new IMPL)
	{
		LoadOpenGLFunctions();
	}

	OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
	{
		delete mImpl;
	}

	void OpenGLGraphicsDevice::Tick()
	{
		f32 color[4] = {0.1f, 0.1f, 0.1f, 1.f};
		
		for (auto& context : mImpl->mContextList)
		{
			wglMakeCurrent(context.hdc, context.hglrc);

			//gl::ClearColor(color[0], color[1], color[2], color[3]);
			//gl::Clear(GL_COLOR_BUFFER_BIT);
			
			SwapBuffers(context.hdc);
		}
	}
	
	void OpenGLGraphicsDevice::CreateContext(const AppWindow* appWindow)
	{
		Win32WindowContext context{};
		context.hwnd = (HWND)appWindow->GetHandle();
		context.hdc = GetDC(context.hwnd);

		auto [format, desc] = GetOpenGLPixelFormat();

		SetPixelFormat(context.hdc, format, &desc);

		context.hglrc = wglCreateContext(context.hdc);
		wglMakeCurrent(context.hdc, context.hglrc);

		if (!mImpl->mContextList.empty())
		{
			wglShareLists(mImpl->mContextList.front().hglrc, context.hglrc);
		}

		mImpl->mContextList.push_back(context);
	}

	void OpenGLGraphicsDevice::DestroyContext(const AppWindow* appWindow)
	{
		auto handle = (HWND)appWindow->GetHandle();

		for (auto Iter = mImpl->mContextList.begin(); Iter != mImpl->mContextList.end(); Iter++)
		{
			if (Iter->hwnd == handle)
			{
				wglMakeCurrent(nullptr, nullptr);
				wglDeleteContext(Iter->hglrc);
				ReleaseDC(Iter->hwnd, Iter->hdc);

				mImpl->mContextList.erase(Iter);
				break;
			}
		}
	}
}

namespace arc::graphics_device
{
	struct OpenGLContext : IContext
	{
		OpenGLContext()
		{
			SetContext(this);
		}

		std::unique_ptr<GraphicsDevice> create_device() override
		{
			return std::make_unique<OpenGLGraphicsDevice>();
		}
	};

	OpenGLContext sContext;

	u32 ArcOpenGLVersion()
	{
		return 1;
	}
}