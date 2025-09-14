#pragma once
#include "Core/Window.h"

#ifdef ARC_GRAPHICS_EXPORT
#define ARC_GRAPHICS_API __declspec(dllexport)
#else
#define ARC_GRAPHICS_API __declspec(dllimport)
#endif // ARC_GRAPHICS_EXPORT

namespace arc
{
	struct GraphicsDeviceSetupInfo
	{
		std::shared_ptr<AppWindow> window;
	};

	class ARC_GRAPHICS_API GraphicsDevice
	{
	public:
		GraphicsDevice() = default;
		virtual ~GraphicsDevice() = default;

		virtual void Tick() = 0;

		virtual void CreateContext(const AppWindow* Info) = 0;
		virtual void DestroyContext(const AppWindow* Info) = 0;
	};

	namespace graphics_device
	{
		std::unique_ptr<GraphicsDevice> ARC_GRAPHICS_API Create();

		struct IContext
		{
			virtual std::unique_ptr<GraphicsDevice> create_device() = 0;
		};

		void ARC_GRAPHICS_API SetContext(IContext* pInterface);
	}
}