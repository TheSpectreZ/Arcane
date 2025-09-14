#pragma once
#include "Graphics/GraphicsDevice.h"

#ifdef ARC_OPENGL_EXPORT
#define ARC_OPENGL_API __declspec(dllexport)
#else
#define ARC_OPENGL_API __declspec(dllimport)
#endif // ARC_VULKAN_EXPORT

namespace arc
{
	class ARC_OPENGL_API OpenGLGraphicsDevice : public GraphicsDevice
	{
	public:
		OpenGLGraphicsDevice();
		~OpenGLGraphicsDevice() override;
		
		void Tick() override;

		void CreateContext(const AppWindow* appWindow) override;
		void DestroyContext(const AppWindow* appWindow) override;
	private:
		struct IMPL;
		IMPL* mImpl;
	};

	namespace graphics_device
	{
		extern "C" ARC_OPENGL_API u32 ArcOpenGLVersion();
	}
}